/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:20:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/14 15:57:00 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		nb_file(t_folder *pfolder, t_option option)
{
	DIR				*dirp;
	struct dirent	*dirc;
	int				i;

	i = 0;
	if ((dirp = opendir(pfolder->path)) != NULL)
		while ((dirc = readdir(dirp)) != NULL)
		{
			if (!test_lawaccess(pfolder->path, dirc->d_name))
				return (-1);
			if (dirc->d_name[0] != '.' || option.a)
				i++;
		}
	else
		pexit(ft_strjoin("nb_file opendir ", pfolder->path));
	if (ft_strcmp(pfolder->path, "/dev/fd") == 0 ||
			ft_strcmp(pfolder->path, "/dev/fd/") == 0)
		i--;
	pfolder->nb_file = i;
	if (closedir(dirp) != 0)
		pexit(ft_strjoin("nb_file closedir ", pfolder->path));
	return (i);
}

static void		fill_subfolder(t_folder *new, t_folder *tmp,
		const t_folder *begin, t_option option)
{
	new->next = tmp->next;
	tmp->next = new;
	tmp = new;
	tmp->next = select_dir(new, begin, option);
}

static t_folder	*recursive_option(t_folder *p,
		const t_folder *begin, t_option option)
{
	t_folder	*new;
	t_folder	*tmp;
	t_folder	*rtr;
	int			i;

	option.r ? (i = p->nb_file - 1) :
		(i = 0);
	rtr = NULL;
	tmp = p;
	while ((!option.r && p->file[i].name != 0) || (option.r && i >= 0))
	{
		if (S_ISDIR(p->file[i].pstat.st_mode) && can_open_folder(p->file[i].name))
		{
			new = NULL;
			new = malloc_pfolder(p->file[i].path);
			if (tmp == p)
				rtr = new;
			fill_subfolder(new, tmp, begin, option);
			while (tmp->next)
				tmp = tmp->next;
		}
		(option.r) ? i-- : i++;
	}
	return (rtr);
}

static int		dir_process(t_folder *pfolder, DIR *dirp,
		t_option option)
{
	struct dirent	*dirc;
	int				i;

	if (nb_file(pfolder, option) == -1)
		return (0);
	if (!(pfolder->file = malloc(sizeof(t_file) * (pfolder->nb_file + 1))))
		exit(-1);
	i = 0;
	while ((dirc = readdir(dirp)) != NULL)
	{
		if (dirc->d_name[0] != '.' || option.a)
		{
			memset_file(&pfolder->file[i]);
			pfolder->file[i].name = ft_strdup(dirc->d_name);
			set_stat(pfolder, &(pfolder->file[i++]));
			if (option.l)
				ell_option(pfolder, &pfolder->file[i - 1], option);
		}
	}
	pfolder->file[i].name = 0;
	if (option.t)
		sort_time(pfolder);
	else if (!option.f)
		sort_ascii(pfolder);
	if (closedir(dirp) != 0)
		pexit(pfolder->path);
	return (1);
}

t_folder		*select_dir(t_folder *pfolder, const t_folder *begin,
		t_option option)
{
	char			*tmp;
	DIR				*dirp;

	dirp = NULL;
	if (pfolder != begin)
		ft_printf("\n%s:\n", pfolder->path);
	if ((dirp = opendir(pfolder->path)) != NULL)
	{
		if (dir_process(pfolder, dirp, option))
		{
			display(pfolder, option, 0);
			if (option.rec)
				return (recursive_option(pfolder, begin, option));
		}
	}
	else
	{
		tmp = ft_strjoin("ft_ls: ", str_withoutpath(pfolder->path));
		perror(tmp);
		free(tmp);
	}
	return (NULL);
}
