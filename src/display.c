/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:08:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/13 15:38:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static int	*espace(int *tab, t_folder *p, t_option option)
{
	int		i;

	if (!(tab = malloc(sizeof(int) * 4)))
		exit(-1);
	i = -1;
	while (++i < 4)
		tab[i] = 0;
	i = -1;
	while (p->file[++i].name != 0)
	{
		if (tab[0] < ft_strlen(p->file[i].owner))
			tab[0] = ft_strlen(p->file[i].owner);
		if (tab[1] < ft_strlen(p->file[i].group))
			tab[1] = ft_strlen(p->file[i].group);
		if (tab[2] < ft_strlen(ft_itoa(p->file[i].bytes)))
			tab[2] = ft_strlen(ft_itoa(p->file[i].bytes));
		if (tab[2] < 8 && p->file[i].major)
			tab[2] = 8;
		if (tab[3] < ft_strlen(ft_itoa(p->file[i].nlink)))
			tab[3] = ft_strlen(ft_itoa(p->file[i].nlink));
	}
	return (tab);
}

static int	*colonne(int *tab, t_folder *p, t_option option)
{
	int		i;
	int		word_size;
	int		nb_file_a;
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	if (!(tab = malloc(sizeof(int) * 3)))
		exit(-1);
	word_size = 0;
	nb_file_a = 0;
	i = -1;
	while (++i < 3)
		tab[i] = 0;
	i = -1;
	while (p->file[++i].name != 0)
	{
		if (word_size < ft_strlen(p->file[i].name))
			word_size = ft_strlen(p->file[i].name);
	}
	tab[0] = word_size + 1;
	tab[1] = w.ws_col / (word_size + 1);
	tab[2] = p->nb_file / tab[1];
	if (tab[2] == 0)
		tab[2] = 1;
	//ft_printf("%d %d %d %d %d\n", w.ws_col, tab[0], tab[1], tab[2], p->nb_file);
	return (tab);
}

static void	big_print(t_folder *p, int j, int *tab, t_option option)
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

void		display(t_folder *p, t_option option)
{
	int		i;
	int		*tab;

	option.r ? (i = p->nb_file - 1) :
		(i = 0);
	if (option.l)
	{
		if (p->file[0].name != 0)
			ft_printf("total %lld\n", p->total_blocks);
		tab = espace(tab, p, option);
	}
	else
		tab = colonne(tab, p, option);
	while ((!option.r && p->file[i].name != 0) || (option.r && i >= 0))
	{
		if (option.l)
			big_print(p, i, tab, option);
		else
		{
			ft_printf("%s\n", p->file[i].name);
			/*
			if ((!option.r && i % tab[1] == 0 && i != 0) || (!option.r && (p->nb_file - i) % tab[1] == 0 && i != p->nb_file))
				printf("%-*s\n", tab[0], p->file[i * tab[2]].name);
			else
				printf("%-*s", tab[0], p->file[i * tab[2]].name);
				*/
		}
		option.r ? i-- : i++;
	}
	if (option.l)
		free(tab);
}

void		display_file(t_folder *pfolder, t_option option)
{
	int i;

	i = -1;
	if (option.l)
		while (pfolder->file[++i].name != 0)
			ell_option(pfolder, &pfolder->file[i], option);
	if (option.t)
		sort_time(pfolder);
	else if (!option.f)
		sort_ascii(pfolder);
	display(pfolder, option);
	if (pfolder->next)
		ft_putchar('\n');
}
