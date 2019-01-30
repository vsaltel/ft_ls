/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_option.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:09:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/30 14:08:42 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	fill_other(t_file *pfile, struct stat pstat)
{
	pfile->nlink = pstat.st_nlink;
	pfile->owner = getpwuid(pstat.st_uid)->pw_name;
	pfile->group = getgrgid(pstat.st_gid)->gr_name;
	pfile->bytes = pstat.st_size;
	pfile->date = ft_strdup(&ctime(&pstat.st_mtimespec.tv_sec)[4]);
	pfile->date[12] = '\0';
}

void	fill_mode(t_file *pfile, struct stat pstat)
{
	if (!(pfile->mode = malloc(sizeof(char) * 12)))
		exit(-1);
	(S_ISDIR(pstat.st_mode)) ? (pfile->mode[0] = 'd') : (pfile->mode[0] = '-');
	((pstat.st_mode & (S_IRUSR)) != 0) ? (pfile->mode[1] = 'r') : (pfile->mode[1] = '-');
	((pstat.st_mode & (S_IWUSR)) != 0) ? (pfile->mode[2] = 'w') : (pfile->mode[2] = '-');
	((pstat.st_mode & (S_IXUSR)) != 0) ? (pfile->mode[3] = 'x') : (pfile->mode[3] = '-');
	((pstat.st_mode & (S_IRGRP)) != 0) ? (pfile->mode[4] = 'r') : (pfile->mode[4] = '-');
	((pstat.st_mode & (S_IWGRP)) != 0) ? (pfile->mode[5] = 'w') : (pfile->mode[5] = '-');
	((pstat.st_mode & (S_IXGRP)) != 0) ? (pfile->mode[6] = 'x') : (pfile->mode[6] = '-');
	((pstat.st_mode & (S_IROTH)) != 0) ? (pfile->mode[7] = 'r') : (pfile->mode[7] = '-');
	((pstat.st_mode & (S_IWOTH)) != 0) ? (pfile->mode[8] = 'w') : (pfile->mode[8] = '-');
	((pstat.st_mode & (S_IXOTH)) != 0) ? (pfile->mode[9] = 'x') : (pfile->mode[9] = '-');
	//pfile->mode[10] = ' '; //TODO @ +
	pfile->mode[10] = '\0';
}

void	ell_option(t_folder *pfolder, t_file *pfile)
{
	struct stat pstat;
	char		*buf;

	if (!(buf = malloc(sizeof(char) * strl_pathfile(pfolder->path, pfile->name))))
		exit(-1);
	if (lstat(str_pathfile(buf, pfolder->path, pfile->name), &pstat) == -1)
		perror(buf);
	else
	{
		fill_mode(pfile, pstat);	
		fill_other(pfile, pstat);
	}
	free(buf);
}	
