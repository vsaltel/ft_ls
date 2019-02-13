/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/13 17:55:24 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				exists(t_file *pfile, char *file)
{
	struct stat	pstat;
	char		*tmp;

	if (!file || stat(file, &pstat) == -1)
	{
		tmp = ft_strjoin("ft_ls: ", file);
		perror(tmp);
		free(tmp);
		tmp = NULL;
		return (0);
	}
	if (S_ISDIR(pstat.st_mode))
		return (1);
	else
	{
		pfile->pstat = pstat;
		return (2);
	}
}

char			*str_withoutpath(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (i--)
		if (str[i] == '/')
			return (str + i + 1);
	return (str);
}

static char		*str_pathfile(char *dst, const char *s1, const char *s2)
{
	int i;

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

static int		strl_pathfile(const char *s1, const char *s2)
{
	int i;
	int y;

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
