/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:20:14 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/18 12:37:21 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			*malloc_tab(size_t len)
{
	int		*tab;
	size_t	i;

	if (!(tab = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	i = -1;
	while (++i < len)
		tab[i] = 0;
	return (tab);
}

t_file		*get_lstfile(t_file *files, size_t index)
{
	if (!files)
		return (NULL);
	while (index--)
		files = files->next;
	return (files);
}

static int	set_option_next(t_option *option, char *str, int i)
{
	if (str[i] == 'l')
	{
		option->un = 0;
		option->l = 1;
		option->c = 0;
		return (1);
	}
	else if (str[i] == '1')
	{
		option->un = 1;
		option->l = 0;
		return (1);
	}
	else if (str[i] == 'C')
	{
		option->c = 1;
		option->l = 0;
		return (1);
	}
	else if (str[i] == 'R')
	{
		option->rec = 1;
		return (1);
	}
	return (0);
}

void		set_option(t_option *option, char *str)
{
	int i;

	i = 0;
	while (str[++i])
		if (!set_option_next(option, str, i))
		{
			if (str[i] == 'a')
				option->a = 1;
			else if (str[i] == 'r')
				option->r = 1;
			else if (str[i] == 't')
				option->t = 1;
			else if (str[i] == 'f')
				option->f = 1;
			else
			{
				write(2, "ft_ls: illegal option -- ", 25);
				write(2, &str[i], 1);
				write(2, "\nusage: ft_ls [-lRartf] [file ...]\n", 35);
				exit(1);
			}
		}
}
