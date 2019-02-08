/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/08 12:03:58 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	pexit(char *str)
{
	perror(str);
	exit(-1);
}

void	memset_option(t_option *option)
{
	option->argc = 0;
	option->l = 0;
	option->rec = 0;
	option->a = 0;
	option->r = 0;
	option->t = 0;
	option->f = 0;
}

void	memset_file(t_file *pfile)
{
	pfile->name = NULL;
	pfile->mode = NULL;
	pfile->extand_perm = ' ';
	pfile->nlink = 0;
	pfile->owner = NULL;
	pfile->group = NULL;
	pfile->bytes = 0;
	pfile->date = NULL;
	pfile->path_link = NULL;
}

char	*str_withoutpath(char *str)
{
	int i;
	int nb;

	i = 0;
	if (!str)
		return (0);
	while (str[i])	
	{
		if (str[i] == '/')
			nb = i;	
		i++;
	}
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

void	set_stat(t_folder *pfolder, t_file *pfile)
{
	char		*buf;

	if (!(buf = malloc(sizeof(char) * strl_pathfile(pfolder->path, pfile->name))))
		exit(-1);
	if (lstat(str_pathfile(buf, pfolder->path, pfile->name), &(pfile->pstat)) == -1)
		perror(buf);
	pfile->path = buf;
}

void	free_folder(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	t_folder	*tmp;
	int			i;

	begin = pfolder;
	while (pfolder)
	{
		i = 0;
		if (pfolder->file)
		{
			while (pfolder->file[i].name != 0)
			{
				free(pfolder->file[i].name);
				free(pfolder->file[i].path);
				if (option.l)
				{
					free(pfolder->file[i].mode);
					free(pfolder->file[i].owner);
					free(pfolder->file[i].group);
					free(pfolder->file[i].date);
				}
				i++;
			}
			free(pfolder->file[i].name);
			free(pfolder->file);
			pfolder->file = NULL;
		}
		free(pfolder->path);
		tmp = pfolder;
		pfolder = pfolder->next;
		free(tmp);
		tmp = NULL;
	}
	pfolder = begin;
}
