/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:20:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/22 18:06:14 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

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

static t_folder	*recursive_option(t_folder *pfolder, t_option option)
{
	struct stat pstat;
	char *buf;
	t_folder *new;
	t_folder *tmp;
	t_folder *rtr;
	int i;

		//"S_IRUSR", "S_IWUSR", "S_IXUSR", "S_IRGRP", "S_IWGRP", "S_IXGRP", "S_IROTH", "S_IWOTH", "S_IXOTH"
	i = 0;
	buf = NULL;
	new = NULL;
	rtr = NULL;
	tmp = pfolder;
	while (pfolder->file[i].name != 0)
	{
		if (!(buf = malloc(sizeof(char) * strl_pathfile(pfolder->path, pfolder->file[i].name))))
			exit(-1);
		if (lstat(str_pathfile(buf, pfolder->path, pfolder->file[i].name), &pstat) == -1)
			perror(buf);
			//pexit(ft_strjoin("recursive_option lstat ", buf));
		else if (S_ISDIR(pstat.st_mode) && ((pstat.st_mode & (S_IXOTH | S_IROTH)) != 0) && pfolder->file[i].name[0] != '.')
		{
			new = NULL;
			if (!(new = malloc(sizeof(t_folder))))
				exit(-1);
			if (tmp == pfolder)
				rtr = new;
			new->path = buf;
			buf = NULL;
			new->next = tmp->next;
			tmp->next = new;
			tmp = new;
			tmp->next = select_dir(new, option);
			while (tmp->next)
				tmp = tmp->next;
		}
		else
			free(buf);
		i++;
	}
	return (rtr);
}

t_folder		*select_dir(t_folder *pfolder, t_option option)
{
	struct dirent	*dirc;
	DIR				*dirp;
	int				i;

	dirp = NULL;
	if ((dirp = opendir(pfolder->path)) != NULL)
	{
		nb_file(pfolder);
		if (!(pfolder->file = malloc(sizeof(t_file) * (pfolder->nb_file + 1))))
			exit(-1);
		pfolder->file[pfolder->nb_file].name = 0;
		i = 0;
		while ((dirc = readdir(dirp)) != NULL)
			pfolder->file[i++].name = ft_strdup(dirc->d_name);
		if (closedir(dirp) != 0)
			pexit(ft_strjoin("select_dir closedir ", pfolder->path));
		if (option.R)
			return (recursive_option(pfolder, option));
	}
	else
		pexit(ft_strjoin("select_dir opendir ", pfolder->path));
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
		select_dir(pfolder, option);
		while (pfolder->next && option.R)
			pfolder = pfolder->next;
		if (option.R)
			pfolder->next = tmp;
		pfolder = pfolder->next;
	}
	pfolder = begin;
}
