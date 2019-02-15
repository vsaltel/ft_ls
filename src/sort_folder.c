/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_folder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:15:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/15 19:40:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	lst_len(t_folder *lst)
{
	size_t	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

static void		split_list(t_folder **left, t_folder **right, size_t lstlen)
{
	t_folder	*nlst;
	size_t		mid;

	if (!left)
		return ;
	mid = lstlen / 2;
	*right = *left;
	while (mid-- > 1)
		*right = (*right)->next;
	nlst = (*right)->next;
	(*right)->next = NULL;
	(*right) = nlst;
}

static t_folder	*sort_merge(t_folder *left, t_folder *right, t_option option)
{
	t_folder	*lst;
	long		cmp;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	cmp = ft_strcmp(left->path, right->path);
	if ((cmp < 0 && !option.r) || (cmp > 0 && option.r))
	{
		lst = left;
		lst->next = sort_merge(left->next, right, option);
	}
	else
	{
		lst = right;
		lst->next = sort_merge(left, right->next, option);
	}
	return (lst);
}

void			merge_sort_folder(t_folder **list, t_option option)
{
	size_t		lstlen;
	t_folder	*left;
	t_folder	*right;

	if (!*list || !(*list)->next)
		return ;
	lstlen = lst_len(*list);
	left = *list;
	split_list(&left, &right, lstlen);
	merge_sort_folder(&left, option);
	merge_sort_folder(&right, option);
	*list = sort_merge(left, right, option);
}

void			sort_ascii(char **tab)
{
	char	*tmp;
	int		i;

	i = 0;
	if (tab[i++])
		while (tab[i])
		{
			if (ft_strcmp(tab[i - 1], tab[i]) > 0)
			{
				tmp = tab[i - 1];
				tab[i - 1] = tab[i];
				tab[i] = tmp;
				i = 1;
			}
			else
				i++;
		}
}
