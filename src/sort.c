/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:15:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/04 17:11:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	lst_len(t_folder *lst)
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

void	split_list(t_folder **left, t_folder **right, size_t lstlen)
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

t_folder	*sort_merge(t_folder *left, t_folder *right, t_option option)
{
	t_folder	*lst;
	long		cmp;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	if (option.t)
		cmp = left->nb_file - right->nb_file;
	else
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

void	merge_sort(t_folder **list, t_option option)
{
	size_t		lstlen;
	t_folder	*left;
	t_folder	*right;

	if (!*list || !(*list)->next)
		return ;
	lstlen = lst_len(*list);
	left = *list;
	split_list(&left, &right, lstlen);
	merge_sort(&left, option);
	merge_sort(&right, option);
	*list = sort_merge(left, right, option);
}
