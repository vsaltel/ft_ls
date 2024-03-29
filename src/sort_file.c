/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:15:31 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/20 18:00:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	lst_len(t_file *lst)
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

static long		cmp_sort(t_file *left, t_file *right, t_option option)
{
	long	cmp;

	cmp = 0;
	if (option.s)
		cmp = right->pstat.st_size - left->pstat.st_size;
	else if (option.t)
		cmp = get_ftime(right->pstat, option) - get_ftime(left->pstat, option);
	if (cmp == 0)
		cmp = ft_strcmp(left->name, right->name);
	return (cmp);
}

static void		split_list(t_file **left, t_file **right, size_t lstlen)
{
	t_file	*nlst;
	size_t	mid;

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

static t_file	*sort_merge(t_file *left, t_file *right, t_option option)
{
	t_file	*lst;
	long	cmp;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	cmp = cmp_sort(left, right, option);
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

void			merge_sort_file(t_file **list, t_option option)
{
	size_t	lstlen;
	t_file	*left;
	t_file	*right;

	if (!*list || !(*list)->next)
		return ;
	lstlen = lst_len(*list);
	left = *list;
	split_list(&left, &right, lstlen);
	merge_sort_file(&left, option);
	merge_sort_file(&right, option);
	*list = sort_merge(left, right, option);
}
