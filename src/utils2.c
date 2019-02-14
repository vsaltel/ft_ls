/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:32:09 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/14 15:56:48 by vsaltel          ###   ########.fr       */
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
	option->un = 0;
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

int		can_open_folder(char *folder)
{
	size_t	len;

	if (!folder)
		return (0);
	len = ft_strlen(folder);
	if (len == 0)
		return (0);
	else if (folder[0] == '.' && len == 1)
		return (0);
	else if (folder[0] == '.' && folder[1] == '.' && len == 2)
		return (0);
	return (1);
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
