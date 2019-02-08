/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:08:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/08 16:56:41 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		*espace(int *tab, t_folder *p, t_option option)
{
	int		i;

	tab = malloc(sizeof(int) * 4);
	i = -1;
	while (++i < 4)
		tab[i] = 0;
	i = -1;
	while (p->file[++i].name != 0)
	{
		if (tab[0] < ft_strlen(p->file[i].owner) &&
				(p->file[i].name[0] != '.' || option.a))
			tab[0] = ft_strlen(p->file[i].owner);
		if (tab[1] < ft_strlen(p->file[i].group) &&
				(p->file[i].name[0] != '.' || option.a))
			tab[1] = ft_strlen(p->file[i].group);
		if (tab[2] < ft_strlen(ft_itoa(p->file[i].bytes)) &&
				(p->file[i].name[0] != '.' || option.a))
			tab[2] = ft_strlen(ft_itoa(p->file[i].bytes));
		if (tab[2] < 8 && p->file[i].major)
			tab[2] = 8;
		if (tab[3] < ft_strlen(ft_itoa(p->file[i].nlink)) &&
				(p->file[i].name[0] != '.' || option.a))
			tab[3] = ft_strlen(ft_itoa(p->file[i].nlink));
	}
	return (tab);
}

void	big_print(t_folder *p, int j, int *tab, t_option option)
{
	if (p->file[j].mode[0] == 'l')
		printf("%s%-1c %*d %-*s  %-*s  %*d %s %s -> %s\n",
			p->file[j].mode, p->file[j].extand_perm, tab[3], p->file[j].nlink,
			tab[0], p->file[j].owner, tab[1], p->file[j].group,
			tab[2], p->file[j].bytes, p->file[j].date,
			p->file[j].name, p->file[j].path_link);
	else if (p->file[j].mode[0] == 'c' || p->file[j].mode[0] == 'b')
		printf("%s%-1c %*d %-*s  %-*s  %*d, %3d %s %s\n",
			p->file[j].mode, p->file[j].extand_perm, tab[3], p->file[j].nlink,
			tab[0], p->file[j].owner, tab[1], p->file[j].group,
			tab[2] - 5 >= 0 ? tab[2] - 5 : 0, p->file[j].major,
			p->file[j].minor, p->file[j].date, p->file[j].name);
	else
		printf("%s%c %*d %-*s  %-*s  %*d %s %s\n",
			p->file[j].mode, p->file[j].extand_perm, tab[3], p->file[j].nlink,
			tab[0], p->file[j].owner, tab[1], p->file[j].group,
			tab[2], p->file[j].bytes, p->file[j].date, p->file[j].name);
}

void	display(t_folder *p, t_option option)
{
	int		j;
	int		*tab;

	option.r ? (j = p->nb_file - 1) :
		(j = 0);
	if (option.l)
	{
		if (p->file[2].name != 0 || option.a)
			ft_printf("total %lld\n", p->total_blocks);
		tab = espace(tab, p, option);
	}
	while ((!option.r && p->file[j].name != 0) || (option.r && j >= 0))
	{
		if ((p->file[j].name[0] != '.' && !option.a) || option.a)
		{
			if (option.l)
				big_print(p, j, tab, option);
			else
				ft_printf("%s\n", p->file[j].name);
		}
		option.r ? j-- : j++;
	}
	if (option.l)
		free(tab);
}

void	sort_ascii(t_folder *pfolder)
{
	t_file	tmp;
	int		i;

	i = 0;
	if (pfolder->file[i++].name != 0)
		while (pfolder->file[i].name != 0)
		{
			if (ft_strcmp(pfolder->file[i - 1].name, pfolder->file[i].name) > 0)
			{
				tmp = pfolder->file[i - 1];
				pfolder->file[i - 1] = pfolder->file[i];
				pfolder->file[i] = tmp;
				i = 1;
			}
			else
				i++;
		}
}

void	sort_time(t_folder *pfolder)
{
	t_file	tmp;
	int		i;

	i = 0;
	if (pfolder->file[i++].name != 0)
		while (pfolder->file[i].name != 0)
		{
			if (pfolder->file[i - 1].pstat.st_mtimespec.tv_sec <
					pfolder->file[i].pstat.st_mtimespec.tv_sec)
			{
				tmp = pfolder->file[i - 1];
				pfolder->file[i - 1] = pfolder->file[i];
				pfolder->file[i] = tmp;
				i = 1;
			}
			else
				i++;
		}
}
