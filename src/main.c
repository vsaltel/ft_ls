/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/01/10 14:35:14 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

/* --(a retirer avant de last push)-- */
t_folder	*test_option(t_folder *pfolder, t_option option)
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
	return (begin);
}
/* ---------------------------------- */

t_folder	*display(t_folder *pfolder, t_option option)
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
			printf("\n");
		pfolder = pfolder->next;
	}
	return (begin);
}

int		main(int argc, char **argv)
{
	t_option	option;	
	t_folder	*pfolder;
	t_folder	*begin;
	int			i;

	pfolder = NULL;
	begin = parse_options(pfolder, &option, argc, argv);
	pfolder = begin;
	i = 0;
	while (pfolder)
	{
		select_dir(pfolder, option);
		pfolder = pfolder->next;
	}
	pfolder = begin;
	pfolder = display(pfolder, option);
	pfolder = test_option(pfolder, option);
	pfolder = closealldir(pfolder);
	return (0);
}
