/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/18 14:20:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	display_files(t_folder *pfolder, t_option option)
{
	t_file	*current;

	current = pfolder->file;
	if (option.l)
		while (current)
		{
			ell_option(pfolder, current, option);
			current = current->next;
		}
	display(pfolder, option, 1);
	if (pfolder->next)
		ft_putchar('\n');
}

static void	fill_list(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	t_folder	*tmp;

	pfolder = pfolder->next;
	begin = pfolder;
	while (pfolder)
	{
		tmp = pfolder->next;
		if (pfolder == begin && option.argc > 1)
			ft_printf("%s:\n", pfolder->path);
		select_dir(pfolder, begin, option);
		while (pfolder->next && option.rec)
			pfolder = pfolder->next;
		if (option.rec)
			pfolder->next = tmp;
		pfolder = pfolder->next;
	}
	pfolder = begin;
}

int			main(int argc, char **argv)
{
	t_option	option;
	t_folder	*pfolder;

	sort_ascii(&(argv[1]));
	pfolder = parse_options(pfolder, &option, argc, argv);
	if (!option.f)
	{
		merge_sort_file(&(pfolder->file), option);
		merge_sort_folder(&(pfolder->next), option);
	}
	else
	{
		option.a = 1;
		option.t = 0;
		option.r = 0;
	}
	option.un = (!isatty(1) && !option.c && !option.l);
	if (pfolder->nb_file)
		display_files(pfolder, option);
	fill_list(pfolder, option);
	free_folder(pfolder, option);
	return (0);
}
