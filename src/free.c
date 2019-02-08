/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:34:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/08 15:42:23 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_file(t_file *pfile, t_option option)
{
	free(pfile->name);
	free(pfile->path);
	if (option.l)
	{
		free(pfile->mode);
		free(pfile->owner);
		free(pfile->group);
		free(pfile->date);
	}
}

void	free_folder(t_folder *pfolder, t_option option)
{
	t_folder	*begin;
	t_folder	*tmp;
	int			i;

	begin = pfolder;
	while (pfolder)
	{
		i = 0;
		if (pfolder->file)
		{
			while (pfolder->file[i].name != 0)
				free_file(&(pfolder->file[i++]), option);
			free(pfolder->file[i].name);
			free(pfolder->file);
			pfolder->file = NULL;
		}
		free(pfolder->path);
		tmp = pfolder;
		pfolder = pfolder->next;
		free(tmp);
		tmp = NULL;
	}
	pfolder = begin;
}
