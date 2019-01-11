/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:20:58 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/11 17:13:23 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		nb_file(t_folder *pfolder)
{
	DIR	*dirp;
	struct dirent *dirc;
	int i;

	i = 0;
	if ((dirp = opendir(pfolder->path)) != NULL)
	{
		while ((dirc = readdir(dirp)) != NULL)
			i++;
	}
	pfolder->nb_file = i;
	if (closedir(dirp) != 0)
	{
		perror("closedir :");
		exit(-1);
	}
	return (i);
}

void	tmp(char *path)
{
	printf("recursive, path = %s\n", path);
}

t_folder	*recursive_option(t_folder *pfolder, t_option option)
{
	struct stat pstat;
	char buf[100];
	t_folder *new;
	t_folder *tmp;
	int i;

	i = 0;
	new = NULL;
	tmp = pfolder;
	while (pfolder->file[i].name != 0)
	{
		//printf("%s %d\n",pfolder->file[i].name, i);
		if (stat(str_pathfile(buf, pfolder->path, pfolder->file[i].name), &pstat) == -1)
		{
			perror("stat");
			exit(-1);
		}
		else if (S_ISDIR(pstat.st_mode) && pfolder->file[i].name[0] != '.')
		{
			new = NULL;
			if (!(new = malloc(sizeof(t_folder))))
				exit(-1);
			new->path = ft_strdup(buf);
			//printf("%s\n", new->path);
			new->next = tmp->next;
			tmp->next = new;
			tmp = new;
			select_dir(new, option);
		}
		i++;
	}
	//printf("exit %s\n", pfolder->path);
	return (new);
}

void	select_dir(t_folder *pfolder, t_option option)
{
	struct dirent *dirc;
	int i;

	pfolder->dirp = NULL;
	if ((pfolder->dirp = opendir(pfolder->path)) != NULL)
	{
		nb_file(pfolder);
		if (!(pfolder->file = malloc(sizeof(t_file) * (pfolder->nb_file + 1))))
			exit(-1);
		pfolder->file[pfolder->nb_file].name = 0;
		i = 0;
		while ((dirc = readdir(pfolder->dirp)) != NULL)
			pfolder->file[i++].name = dirc->d_name;
		if (option.R)
			recursive_option(pfolder, option);		
	}
}
