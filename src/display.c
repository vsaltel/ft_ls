/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:51:29 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/01 14:07:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	display(t_folder *pfolder, t_option option)
{
	int j;

	j = 0;
	while (pfolder->file[j].name != 0)
	{
		if ((pfolder->file[j].name[0] != '.' && !option.a) || option.a)
		{
			if (option.l)
				printf("%s %2d %s  %s %6d %s %s\n", pfolder->file[j].mode, pfolder->file[j].nlink, pfolder->file[j].owner, pfolder->file[j].group, pfolder->file[j].bytes, pfolder->file[j].date ,pfolder->file[j].name);
			else
				printf("%s\n", pfolder->file[j].name);
		}
		j++;
	}
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
