/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:08:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/05 18:11:05 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		*espace(t_folder *pfolder, t_option option)
{
	int		*tab;
	int		i;

	tab = malloc(sizeof(int) * 4);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	i = 0;
	while (pfolder->file[i].name != 0)
	{
		if (tab[0] < ft_strlen(pfolder->file[i].owner) && (pfolder->file[i].name[0] != '.' || option.a))
			tab[0] = ft_strlen(pfolder->file[i].owner);
		if (tab[1] < ft_strlen(pfolder->file[i].group) && (pfolder->file[i].name[0] != '.' || option.a))
			tab[1] = ft_strlen(pfolder->file[i].group);
		if (tab[2] < ft_strlen(ft_itoa(pfolder->file[i].bytes)) && (pfolder->file[i].name[0] != '.' || option.a))
			tab[2] = ft_strlen(ft_itoa(pfolder->file[i].bytes));
		if (tab[3] < ft_strlen(ft_itoa(pfolder->file[i].nlink)) && (pfolder->file[i].name[0] != '.' || option.a))
			tab[3] = ft_strlen(ft_itoa(pfolder->file[i].nlink));
		i++;
	}
	return (tab);
}

void	display(t_folder *pfolder, t_option option)
{
	int j;
	int		*tab;

	j = 0;
	if (option.l)
	{
		ft_printf("total %lld\n", pfolder->total_blocks);
		tab = espace(pfolder, option);
	}
	while (pfolder->file[j].name != 0)
	{
		if ((pfolder->file[j].name[0] != '.' && !option.a) || option.a)
		{
			if (option.l)
			{
				if (pfolder->file[j].mode[0] == 'l')
					printf("%s%-1c %*d %-*s  %-*s  %*d %s %s -> %s\n", pfolder->file[j].mode, pfolder->file[j].extand_perm, tab[3], pfolder->file[j].nlink, tab[0], pfolder->file[j].owner, tab[1], pfolder->file[j].group, tab[2], pfolder->file[j].bytes, pfolder->file[j].date, pfolder->file[j].name, pfolder->file[j].path_link);
				else if (pfolder->file[j].mode[0] == 'c')
					printf("%s%-1c %*d %-*s  %-*s  %*d, %4d %s %s\n", pfolder->file[j].mode, pfolder->file[j].extand_perm, tab[3], pfolder->file[j].nlink, tab[0], pfolder->file[j].owner, tab[1], pfolder->file[j].group, tab[2], pfolder->file[j].major, pfolder->file[j].minor, pfolder->file[j].date, pfolder->file[j].name);
				else
					printf("%s%-1c %*d %-*s  %-*s  %*d %s %s\n", pfolder->file[j].mode, pfolder->file[j].extand_perm, tab[3], pfolder->file[j].nlink, tab[0], pfolder->file[j].owner, tab[1], pfolder->file[j].group, tab[2], pfolder->file[j].bytes, pfolder->file[j].date, pfolder->file[j].name);
			}
			else
				ft_printf("%s\n", pfolder->file[j].name);
		}
		j++;
	}
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
