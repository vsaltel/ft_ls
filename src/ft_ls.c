/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:20:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/06 17:20:48 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		nb_file(t_folder *pfolder)
{
	DIR				*dirp;
	struct dirent	*dirc;
	int				i;

	i = 0;
	if ((dirp = opendir(pfolder->path)) != NULL)
		while ((dirc = readdir(dirp)) != NULL)
			i++;
	else
		pexit(ft_strjoin("nb_file opendir ", pfolder->path));
	pfolder->nb_file = i;
	if (closedir(dirp) != 0)
		pexit(ft_strjoin("nb_file closedir ", pfolder->path));
	return (i);
}

static t_folder	*recursive_option(t_folder *pfolder, const t_folder *begin, t_option option)
{
	t_folder	*new;
	t_folder	*tmp;
	t_folder	*rtr;
	int			i;

	//"S_IRUSR", "S_IWUSR", "S_IXUSR", "S_IRGRP", "S_IWGRP", "S_IXGRP", "S_IROTH", "S_IWOTH", "S_IXOTH"
	i = 0;
	new = NULL;
	rtr = NULL;
	tmp = pfolder;
	while (pfolder->file[i].name != 0)
	{
		if (S_ISDIR(pfolder->file[i].pstat.st_mode) /*&& ((pfolder->file[i].pstat.st_mode & (S_IXOTH | S_IROTH)) != 0)*/ && (pfolder->file[i].name[0] != '.' || (option.a && can_open_folder(pfolder->file[i].name))))
		{
			new = NULL;
			new = malloc_pfolder(pfolder->file[i].path);
			if (tmp == pfolder)
				rtr = new;
			new->next = tmp->next;
			tmp->next = new;
			tmp = new;
			tmp->next = select_dir(new, begin, option);
			while (tmp->next)
				tmp = tmp->next;
		}
		i++;
	}
	return (rtr);
}

t_folder		*select_dir(t_folder *pfolder, const t_folder *begin,
		t_option option)
{
	char			*tmp;
	struct dirent	*dirc;
	DIR				*dirp;
	int				i;

	dirp = NULL;
	if (pfolder != begin)
		ft_printf("\n%s:\n", pfolder->path);
	if ((dirp = opendir(pfolder->path)) != NULL)
	{
		nb_file(pfolder);
		if (!(pfolder->file = malloc(sizeof(t_file) * (pfolder->nb_file + 1))))
			exit(-1);
		i = 0;
		while ((dirc = readdir(dirp)) != NULL)
		{
			memset_file(&pfolder->file[i]);
			pfolder->file[i].name = ft_strdup(dirc->d_name);
			set_stat(pfolder, &(pfolder->file[i++]));
			if (option.l)
				ell_option(pfolder, &pfolder->file[i - 1], option);
		}
		pfolder->file[i].name = 0;
		option.t ? sort_time(pfolder) : sort_ascii(pfolder);
		if (closedir(dirp) != 0)
			pexit(pfolder->path);
		display(pfolder, option);
		if (option.rec)
			return (recursive_option(pfolder, begin, option));
	}
	else
	{
		tmp = ft_strjoin("ft_ls: ", str_withoutpath(pfolder->path));
		perror(tmp);
		free(tmp);
	}
	return (NULL);
}

void			fill_list(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	t_folder	*tmp;

	begin = pfolder;
	while (pfolder)
	{
		tmp = pfolder->next;
		if ((pfolder->next != NULL && pfolder == begin) && option.argc > 1)
			ft_printf("%s:\n", pfolder->path);
		select_dir(pfolder, begin, option);
		while (pfolder->next && option.rec)
			pfolder = pfolder->next;
		if (option.rec)
			pfolder->next = tmp;
		pfolder = pfolder->next;
	}
	pfolder = begin;
}
