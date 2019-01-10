/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/10 14:35:30 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	memset_option(t_option *option)
{
	option->l = 0;
	option->R = 0;
	option->a = 0;
	option->r = 0;
	option->t = 0;
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
	while (*s1)
		dst[i++] = *s1++;
	if (dst[i - 1] != '/')
		dst[i++] = '/';
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

t_folder	*closealldir(t_folder *pfolder)
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
	return (begin);
}
