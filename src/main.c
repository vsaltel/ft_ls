/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/15 19:40:49 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	is_term(t_option *option)
{
	if (!isatty(1) && !option->c && !option->l)
		option->un = 1;
}

void	fill_list(t_folder *pfolder, t_option option)
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

int		main(int argc, char **argv)
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
	is_term(&option);
	if (pfolder->nb_file)
		display_file(pfolder, option);
	fill_list(pfolder, option);
	free_folder(pfolder, option);
	return (0);
}
