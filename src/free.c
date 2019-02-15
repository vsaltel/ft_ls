/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:34:32 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/15 14:50:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_file(t_file *pfile, t_option option)
{
	if (!pfile)
		return ;
	free(pfile->name);
	if (pfile->path)
		free(pfile->path);
	if (option.l)
	{
		free(pfile->mode);
		free(pfile->owner);
		free(pfile->group);
		free(pfile->date);
	}
	free(pfile);
}

void	free_files(t_file *files, t_option option)
{
	t_file	*current;
	t_file	*next;

	current = files;
	while (current)
	{
		next = current->next;
		free_file(current, option);
		current = next;
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
			free_files(pfolder->file, option);
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
