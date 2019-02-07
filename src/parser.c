/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:24:49 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/07 18:45:29 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			exists(char *file)
{
	DIR *folder;
	char *tmp;

	if (!file || !(folder = opendir(file)))
	{
		tmp = ft_strjoin("ft_ls: ", file);
		perror(tmp);
		free(tmp);
		tmp = NULL;
		return (0);
	}
	else
		closedir(folder);
	return (1);
}

t_folder	*malloc_pfolder(char *path)
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

void		set_option(t_option *option, char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'l')
			option->l = 1;
		else if (str[i] == 'R')
			option->rec = 1;
		else if (str[i] == 'a')
			option->a = 1;
		else if (str[i] == 'r')
			option->r = 1;
		else if (str[i] == 't')
			option->t = 1;
		else if (str[i] == 'f')
		{
			option->f = 1;
			option->a = 1;
		}
		else
		{
			ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-lRartf] [file ...]\n", str[i]);
			exit(-1);
		}
		i++;
	}
}

t_folder	*parse_options(t_folder *pfolder, t_option *option,
		int argc, char **argv)
{
	t_folder *begin;

	memset_option(option);
	argv++;
	while (argc-- > 1)
	{
		if (*argv[0] != '-')
			break ;
		set_option(option, *argv);
		argv++;
	}
	option->argc = argc;
	if (argc > 0)
	{
		while (!exists(*argv) && argc > 0)
		{
			argv = argv + 1;
			--argc;
			option->argc++;
			if (argc == 0)
				exit(-1);
		}
		pfolder = malloc_pfolder(*argv++);
		begin = pfolder;
		while (--argc > 0)
		{
			if (exists(*argv))
			{
				pfolder->next = malloc_pfolder(*argv);
				pfolder = pfolder->next;
			}
			argv = argv + 1;
			option->argc++;
		}
	}
	else
	{
		pfolder = malloc_pfolder(NULL);
		begin = pfolder;
	}
	return (begin);
}
