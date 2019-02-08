/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/08 15:32:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			exists(char *file)
{
	DIR		*folder;
	char	*tmp;

	if (!file || !(folder = opendir(file)))
	{
		tmp = ft_strjoin("ft_ls: ", file);
		perror(tmp);
		free(tmp);
		tmp = NULL;
		return (0);
	}
	else
		closedir(folder);
	return (1);
}

char		*str_withoutpath(char *str)
{
	int i;
	int nb;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '/')
			nb = i;
	return (&str[nb + 1]);
}

static char	*str_pathfile(char *dst, const char *s1, const char *s2)
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

static int	strl_pathfile(const char *s1, const char *s2)
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

void		set_stat(t_folder *pfolder, t_file *pfile)
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
