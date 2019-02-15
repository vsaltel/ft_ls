/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:20:14 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/15 14:29:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		*malloc_tab(size_t len)
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

t_file	*get_lstfile(t_file *files, size_t index)
{
	if (!files)
		return (NULL);
	while (index--)
		files = files->next;
	return (files);
}
