/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:24:49 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/21 14:12:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_folder		*malloc_pfolder(char *path)
{
	t_folder	*pfolder;

	if (!(pfolder = malloc(sizeof(t_folder))))
		exit(-1);
	if (path)
		pfolder->path = ft_strdup(path);
	else
	{
		if (!(pfolder->path = malloc(sizeof(char) * 2)))
			exit(-1);
		pfolder->path[0] = '.';
		pfolder->path[1] = '\0';
	}
	pfolder->next = NULL;
	pfolder->total_blocks = 0;
	pfolder->file = NULL;
	return (pfolder);
}

static t_file	*fill_pfile(t_file *current, t_folder *begin, char **argv)
{
	if (!(current = memset_file(current)))
		exit(-1);
	if (!begin->file)
		begin->file = current;
	current->name = ft_strdup(*argv);
	current->path = ft_strdup(*argv);
	if (lstat(current->name, &(current->pstat)) == -1)
		perror(current->name);
	begin->nb_file++;
	return (current);
}

static t_folder	*fill_pfolder(t_folder *pfolder, t_option *option,
		int argc, char **argv)
{
	int			rtr;
	t_folder	*begin;
	t_file		*current;

	pfolder = malloc_pfolder("file");
	begin = pfolder;
	current = begin->file;
	begin->nb_file = 0;
	while (argc-- > 0)
	{
		if ((rtr = exists(NULL, *argv, *option)))
		{
			if (rtr == 1)
			{
				pfolder->next = malloc_pfolder(*argv);
				pfolder = pfolder->next;
			}
			else if (rtr == 2)
				current = fill_pfile(current, begin, argv);
			else if (rtr == -1)
				exit(1);
		}
		argv = argv + 1;
	}
	return (begin);
}

t_folder		*parse_options(t_folder *pfolder, t_option *option,
		int argc, char **argv)
{
	t_folder *begin;

	while (--argc)
	{
		if ((*argv)[0] != '-' || ((*argv)[0] == '-' && (*argv)[1] == '\0'))
			break ;
		if (ft_strlen(*argv) == 2 && (*argv)[0] == '-' && (*argv)[1] == '-')
		{
			argc--;
			argv++;
			break ;
		}
		set_option(option, *argv);
		argv++;
	}
	sort_ascii(argv);
	option->argc = argc;
	if (argc > 0)
		return (fill_pfolder(pfolder, option, argc, argv));
	pfolder = malloc_pfolder("file");
	begin = pfolder;
	pfolder->next = malloc_pfolder(NULL);
	begin->nb_file = 0;
	return (begin);
}
