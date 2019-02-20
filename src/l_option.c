/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_option.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:09:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/20 17:14:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	fill_time(t_file *pfile, struct stat pstat, t_option option)
{
	char			*str;
	time_t			ftime;
	size_t			i;

	ftime = get_ftime(pstat, option);
	str = ctime(&ftime);
	printf("Time: %s\n", str);
	if (ftime + 15811200 < time(NULL) || ftime - 15811200 > time(NULL))
	{
		i = 19;
		while (str[i] == ' ')
			i++;
		pfile->date = ft_strdup(&str[4]);
		pfile->date[7] = ' ';
		pfile->date[8] = str[i++];
		pfile->date[9] = str[i++];
		pfile->date[10] = str[i++];
		pfile->date[11] = str[i++];
		pfile->date[12] = str[i++];
	}
	else
		pfile->date = ft_strdup(&str[4]);
	pfile->date[12] = '\0';
}

static void	fill_other(t_file *pfile, struct stat pstat, t_option option)
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
	pfile->date = build_time(pfile, pstat, option);
}

static void	law_access(t_file *pfile, struct stat pstat)
{
	pfile->mode[1] = ((pstat.st_mode & (S_IRUSR)) != 0) ? 'r' : '-';
	pfile->mode[2] = ((pstat.st_mode & (S_IWUSR)) != 0) ? 'w' : '-';
	pfile->mode[3] = ((pstat.st_mode & (S_IXUSR)) != 0) ? 'x' : '-';
	if ((pstat.st_mode & (S_ISUID)))
		pfile->mode[3] = pfile->mode[3] == 'x' ? 's' : 'S';
	pfile->mode[4] = ((pstat.st_mode & (S_IRGRP)) != 0) ? 'r' : '-';
	pfile->mode[5] = ((pstat.st_mode & (S_IWGRP)) != 0) ? 'w' : '-';
	pfile->mode[6] = ((pstat.st_mode & (S_IXGRP)) != 0) ? 'x' : '-';
	if ((pstat.st_mode & (S_ISGID)))
		pfile->mode[6] = pfile->mode[6] == 'x' ? 's' : 'S';
	pfile->mode[7] = ((pstat.st_mode & (S_IROTH)) != 0) ? 'r' : '-';
	pfile->mode[8] = ((pstat.st_mode & (S_IWOTH)) != 0) ? 'w' : '-';
	pfile->mode[9] = ((pstat.st_mode & (S_IXOTH)) != 0) ? 'x' : '-';
	if ((pstat.st_mode & (S_ISVTX)))
		pfile->mode[9] = pfile->mode[9] == 'x' ? 't' : 'T';
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
	acl_t	tmp;

	fill_mode(pfile, pfile->pstat);
	fill_other(pfile, pfile->pstat, option);
	pfolder->total_blocks += pfile->pstat.st_blocks;
	if ((tmp = acl_get_file(pfile->path, ACL_TYPE_EXTENDED)))
		pfile->extand_perm = '+';
	acl_free(tmp);
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
