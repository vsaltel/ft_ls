/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/01 14:36:39 by vsaltel          ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	t_option	option;	
	t_folder	*pfolder;

	//test_folder(argv, argc);
	pfolder = parse_options(pfolder, &option, argc, argv);
	fill_list(pfolder, option);	
	//test_option(pfolder, option);
	free_folder(pfolder, option);
	return (0);
}
