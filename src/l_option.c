/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_option.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:09:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/08 13:30:11 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	fill_time(t_file *pfile, struct stat pstat)
{
	char			*str;

	str = ctime(&pstat.st_mtimespec.tv_sec);
	if (time(NULL) - 15811200 < pstat.st_mtimespec.tv_sec)
		pfile->date = ft_strdup(&str[4]);
	else
	{
		pfile->date = ft_strdup(&str[4]);
		pfile->date[7] = str[19];
		pfile->date[8] = str[20];
		pfile->date[9] = str[21];
		pfile->date[10] = str[22];
		pfile->date[11] = str[23];
	}
	pfile->date[12] = '\0';
}

static void	fill_other(t_file *pfile, struct stat pstat)
{
	struct passwd	*pwd;
	struct group	*grp;

	pfile->nlink = pstat.st_nlink;
	if ((pwd = getpwuid(pstat.st_uid)))
		pfile->owner = ft_strdup(pwd->pw_name);
	else
		pfile->owner = ft_itoa(pstat.st_uid);
	if ((grp = getgrgid(pstat.st_gid)))
		pfile->group = ft_strdup(grp->gr_name);
	else
		pfile->group = ft_itoa(pstat.st_gid);
	pfile->major = major(pstat.st_rdev);
	pfile->minor = minor(pstat.st_rdev);
	pfile->bytes = pstat.st_size;
	fill_time(pfile, pstat);
}

static void	law_access(t_file *pfile, struct stat pstat)
{
	((pstat.st_mode & (S_IRUSR)) != 0) ? (pfile->mode[1] = 'r') :
		(pfile->mode[1] = '-');
	((pstat.st_mode & (S_IWUSR)) != 0) ? (pfile->mode[2] = 'w') :
		(pfile->mode[2] = '-');
	((pstat.st_mode & (S_IXUSR)) != 0) ? (pfile->mode[3] = 'x') :
		(pfile->mode[3] = '-');
	((pstat.st_mode & (S_IRGRP)) != 0) ? (pfile->mode[4] = 'r') :
		(pfile->mode[4] = '-');
	((pstat.st_mode & (S_IWGRP)) != 0) ? (pfile->mode[5] = 'w') :
		(pfile->mode[5] = '-');
	((pstat.st_mode & (S_IXGRP)) != 0) ? (pfile->mode[6] = 'x') :
		(pfile->mode[6] = '-');
	((pstat.st_mode & (S_IROTH)) != 0) ? (pfile->mode[7] = 'r') :
		(pfile->mode[7] = '-');
	((pstat.st_mode & (S_IWOTH)) != 0) ? (pfile->mode[8] = 'w') :
		(pfile->mode[8] = '-');
	((pstat.st_mode & (S_IXOTH)) != 0) ? (pfile->mode[9] = 'x') :
		(pfile->mode[9] = '-');
}

static void	fill_mode(t_file *pfile, struct stat pstat)
{
	if (!(pfile->mode = malloc(sizeof(char) * 11)))
		exit(-1);
	pfile->mode[0] = '-';
	if (S_ISBLK(pstat.st_mode))
		(pfile->mode[0] = 'b');
	else if (S_ISCHR(pstat.st_mode))
		(pfile->mode[0] = 'c');
	else if (S_ISDIR(pstat.st_mode))
		(pfile->mode[0] = 'd');
	else if (S_ISLNK(pstat.st_mode))
		(pfile->mode[0] = 'l');
	else if (S_ISSOCK(pstat.st_mode))
		(pfile->mode[0] = 's');
	else if (S_ISFIFO(pstat.st_mode))
		(pfile->mode[0] = 'p');
	law_access(pfile, pstat);
	pfile->mode[10] = '\0';
}

void		ell_option(t_folder *pfolder, t_file *pfile, t_option option)
{
	fill_mode(pfile, pfile->pstat);
	fill_other(pfile, pfile->pstat);
	if (pfile->name[0] != '.' || option.a)
		pfolder->total_blocks += pfile->pstat.st_blocks;
	if (listxattr(pfile->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		pfile->extand_perm = '@';
	if (pfile->mode[0] == 'l')
	{
		if (!(pfile->path_link = malloc(sizeof(char) * BUFF_SIZE)))
			exit(-1);
		ft_memset(pfile->path_link, '\0', BUFF_SIZE);
		readlink(pfile->path, pfile->path_link, BUFF_SIZE - 1);
	}
}
