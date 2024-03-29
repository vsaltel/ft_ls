/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/21 14:13:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				exists(t_file *pfile, char *file, t_option options)
{
	struct stat	pstat;
	struct stat	lstats;
	char		*tmp;
	int			res;
	int			res1;

	res = stat(file, &pstat);
	res1 = lstat(file, &lstats);
	if (!file || (res == -1 && res1 == -1))
	{
		if (file && file[0] == '\0')
			tmp = ft_strdup("ft_ls: fts_open");
		else
			tmp = ft_strjoin("ft_ls: ", file);
		perror(tmp);
		free(tmp);
		return ((file && file[0] == '\0') ? -1 : 0);
	}
	if ((S_ISDIR(pstat.st_mode) && !S_ISLNK(lstats.st_mode)) ||
		(S_ISDIR(pstat.st_mode) && S_ISLNK(lstats.st_mode) && !options.l))
		return (1);
	if (pfile)
		pfile->pstat = S_ISLNK(lstats.st_mode) ? lstats : pstat;
	return (2);
}

static char		*str_pathfile(char *dst, const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1)
		dst[i++] = *s1++;
	if (dst[i - 1] != '/')
		dst[i++] = '/';
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

static size_t	strl_pathfile(const char *s1, const char *s2)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
		i++;
	if (s1[i - 1] != '/')
		i++;
	while (s2[y])
		y++;
	y++;
	return (i + y);
}

int				test_lawaccess(char *path, char *file)
{
	struct stat	pstat;
	char		*buf;
	int			rtr;

	if (!(buf = malloc(sizeof(char) * strl_pathfile(path, file))))
		exit(-1);
	str_pathfile(buf, path, file);
	rtr = stat(buf, &pstat);
	free(buf);
	if (rtr == -1)
		return (0);
	else
		return (1);
}

void			set_stat(t_folder *pfolder, t_file *pfile)
{
	char		*buf;

	if (!(buf = malloc(sizeof(char) *
					strl_pathfile(pfolder->path, pfile->name))))
		exit(-1);
	if (lstat(str_pathfile(buf, pfolder->path, pfile->name),
				&(pfile->pstat)) == -1)
		perror(buf);
	pfile->path = buf;
}
