/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:20:14 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/21 14:15:03 by frossiny         ###   ########.fr       */
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

int			can_add_file(char *name, t_option options)
{
	if (!name || name[0] == '\0')
		return (0);
	if (name[0] != '.')
		return (1);
	if (options.a)
		return (1);
	if (ft_strlen(name) > 1 && !(name[1] == '.' && ft_strlen(name) == 2))
		return (options.ca);
	return (0);
}
