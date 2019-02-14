/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:04:48 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/14 15:14:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_list(t_folder *pfolder, t_option option)
{
	t_folder	*folderfile;
	t_folder	*begin;
	t_folder	*tmp;

	folderfile = pfolder;
	pfolder = pfolder->next;
	begin = pfolder;
	while (pfolder)
	{
		tmp = pfolder->next;
		if (((pfolder->next != NULL || folderfile->nb_file) &&
					pfolder == begin) && option.argc > 1)
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

	pfolder = parse_options(pfolder, &option, argc, argv);
	if (!option.f)
		merge_sort(&(pfolder->next), option);
	else
	{
		option.a = 1;
		option.t = 0;
		option.r = 0;
	}
	if (pfolder->nb_file)
		display_file(pfolder, option);
	fill_list(pfolder, option);
	free_folder(pfolder, option);
	return (0);
}
