/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:12:35 by frossiny          #+#    #+#             */
/*   Updated: 2019/01/28 09:28:39 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_mode(t_file	*file, mode_t	*mode)
{
	if (!file || !mode)
		return ;
	file->mode[0] = (*mode & S_IFMT) == S_IFDIR ? 'd' : '-';
	file->mode[1] = (*mode & S_IRUSR) ? 'r' : '-';
	file->mode[2] = (*mode & S_IWUSR) ? 'w' : '-';
	file->mode[3] = (*mode & S_IXUSR) ? 'x' : '-';
	file->mode[4] = (*mode & S_IRGRP) ? 'r' : '-';
	file->mode[5] = (*mode & S_IWGRP) ? 'w' : '-';
	file->mode[6] = (*mode & S_IXGRP) ? 'x' : '-';
	file->mode[7] = (*mode & S_IROTH) ? 'r' : '-';
	file->mode[8] = (*mode & S_IWOTH) ? 'w' : '-';
	file->mode[9] = (*mode & S_IXOTH) ? 'x' : '-';
	file->mode[10] = '\0';
}

t_file	*read_file(struct dirent *de)
{
	t_file			*file;
	struct stat		stats;
	struct passwd	*user;
	struct group	*group;

	if (!de)
		return (NULL);
	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (stat(de->d_name, &stats) < 0)
		return (NULL);
	if (!(user = getpwuid(stats.st_uid)) || !(group = getgrgid(stats.st_gid)))
		return (NULL);
	file->name = de->d_name;
	file->owner = user->pw_name;
	file->group = group->gr_name;
	//file->bytes = stats.st_size;
	file->date = ctime(&stats.st_ctime);
	//file->links = stats.st_nlink;
	fill_mode(file, &(stats.st_mode));

	return (file);
}

int		main(int argc, char **argv)
{
	char			*path;
	DIR				*directory;
	struct dirent	*de;
	struct stat		stats;
	struct passwd	*user;
	struct group	*group;

	if (argc > 1)
		path = argv[1];
	else
		path = ft_strdup(".");
	directory = opendir(path);
	if (!directory)
		return (-1);
	while ((de = readdir(directory)))
	{
		if (de->d_name[0] != '.')
		{
			t_file	*file = read_file(de);
			ft_printf("%s  %s %s	%5d %s\n", file->mode, file->owner, file->group, file->bytes, file->name);
		}
			/*if (stat(de->d_name, &stats) > -1)
			{
				if (!(user = getpwuid(stats.st_uid)))
					return (-1);
				if (!(group = getgrgid(stats.st_gid)))
					return (-1);
				ft_printf( (((stats.st_mode & S_IFMT) == S_IFDIR)) ? "d" : "-");
				ft_printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
				ft_printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
				ft_printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
				ft_printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
				ft_printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
				ft_printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
				ft_printf( (stats.st_mode & S_IROTH) ? "r" : "-");
				ft_printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
				ft_printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
				ft_printf(" %s %s	%5d %s\n", user->pw_name, group->gr_name, stats.st_size, de->d_name);
			}*/
	}
	closedir(directory);
	return (0);
}
