/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/21 19:52:16 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

/* --(a retirer avant de last push)-- */
static void	test_option(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	int l = 0;

	begin = pfolder;
	printf("----------\n");
	while (pfolder)
	{
		printf("path[%d] = %s\n", l, pfolder->path);
		pfolder = pfolder->next;
		l++;
	}
	printf("l = %d, R = %d, a = %d, r = %d, t = %d", option.l, option.R, option.a, option.r, option.t);
	pfolder = begin;
}
/* ---------------------------------- */

static void	display(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	int j;

	begin = pfolder;
	while (pfolder)
	{
		if (pfolder->next != NULL || pfolder != begin)
			printf("%s:\n", pfolder->path);
		j = 0;
		while (pfolder->file[j].name != 0)
		{
			if ((pfolder->file[j].name[0] != '.' && !option.a) || option.a)
				printf("%s\n", pfolder->file[j].name);
			j++;
		}
		if (pfolder->next != NULL)
			ft_putchar('\n');
		pfolder = pfolder->next;
	}
	pfolder = begin;
}

int			main(int argc, char **argv)
{
	t_option	option;	
	t_folder	*pfolder;

	pfolder = parse_options(pfolder, &option, argc, argv);
	fill_list(pfolder, option);	
	display(pfolder, option);
	test_option(pfolder, option);
	//closealldir(pfolder);
	free_folder(pfolder);
	return (0);
}
