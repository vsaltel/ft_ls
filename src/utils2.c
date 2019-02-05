/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:32:09 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/05 14:10:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

/*
void	test_folder(t_folder *pfolder)
{
	DIR			*dirp;
	t_folder	*begin;
	t_folder	*tmp;

	tmp = NULL;
	while (pfolder)
	{
		dirp = NULL;
		if ((dirp = opendir(pfolder->path)) == NULL)
		{
			perror(pfolder->path);
			if (tmp != NULL)
				tmp->next = pfolder->next;
			if (pfolder == begin)
				begin = begin->next;
			free(pfolder->path);
			free(pfolder);
			pfolder = begin;
			tmp = NULL;
		}
		else
		{
			if (closedir(dirp) != 0)
				pexit(pfolder->path);
			tmp = pfolder;
			pfolder = pfolder->next;
		}
	}
	pfolder = begin;
}
*/

void	test_folder(char **argv, int argc)
{
	int			i;
	DIR			*dirp;

	i = 1;
	argv++;
	while (i < argc)
		if (argv[i++][0] != '-')
			break ;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		dirp = NULL;
		if ((dirp = opendir(argv[i])) == NULL)
		{
			perror(argv[i]);
			argv[i] = 0;
		}
		else
		{
			if (closedir(dirp) != 0)
				pexit(argv[i]);
		}
		i++;
	}
}

int		can_open_folder(char *folder)
{
	size_t	len;

	if (!folder)
		return (0);
	len = ft_strlen(folder);
	if (len == 0)
		return (0);
	else if (folder[0] == '.' && len == 1)
		return (0);
	else if (folder[0] == '.' && folder[1] == '.' && len == 2)
		return (0);
	return (1);
}
