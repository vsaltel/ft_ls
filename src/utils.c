/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/22 16:14:19 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	pexit(char *str)
{
		perror(str);
		exit(-1);
}

void	memset_option(t_option *option)
{
	option->l = 0;
	option->R = 0;
	option->a = 0;
	option->r = 0;
	option->t = 0;
	option->U = 0;
	option->G = 0;
	option->O = 0;
}

void	memset_file(t_file *pfile)
{
	pfile->name = NULL;
	pfile->mode = NULL;
	pfile->nb_links = NULL;
	pfile->owner = NULL;
	pfile->group = NULL;
	pfile->bytes = NULL;
	pfile->date = NULL;
}

char	*str_pathfile(char *dst, const char *s1, const char *s2)
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

int		strl_pathfile(const char *s1, const char *s2)
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
/*
void	closealldir(t_folder *pfolder)
{
	t_folder *begin;

	begin = pfolder;
	while (pfolder)
	{
		if (closedir(pfolder->dirp) != 0)
		{
			perror("closedir :");
			exit(-1);
		}
		pfolder = pfolder->next;
	}
	pfolder = begin;
}
*/
void	free_folder(t_folder *pfolder)
{
	t_folder *begin;
	t_folder *tmp;
	int i;

	begin = pfolder;
	while (pfolder)
	{
		i = 0;
		while (pfolder->file[i].name != 0)
			free(pfolder->file[i++].name);
		free(pfolder->file[i].name);
		free(pfolder->file);
		pfolder->file = NULL;
		free(pfolder->path);
		tmp = pfolder;
		pfolder = pfolder->next;
		free(tmp);
		tmp = NULL;
	}
	pfolder = begin;
}
