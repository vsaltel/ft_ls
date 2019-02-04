/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:24:49 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/04 14:13:27 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		exists(char	*file)
{
	DIR *folder;

	if (!file || !(folder = opendir(file)))
		return (0);
	return (!closedir(folder));
}

void	set_option(t_option *option, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'l')
			option->l = 1;
		if (str[i] == 'R')
			option->R = 1;
		if (str[i] == 'a')
			option->a = 1;
		if (str[i] == 'r')
			option->r = 1;
		if (str[i] == 't')
			option->t = 1;
		if (str[i] == 'f')
			option->f = 1;
		if (str[i] == 'f')
			option->a = 1;
		i++;
	}
}

t_folder	*parse_options(t_folder *pfolder, t_option *option, int argc, char **argv)
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
		while (argc && !exists(*argv))
		{
			perror(*argv++);
			argc--;
		}
		if (argc == 0)
			exit(-1);
		if (!(pfolder = malloc(sizeof(t_folder))))
			exit(-1);
		pfolder->next = NULL;
		pfolder->file = NULL;
		pfolder->path = ft_strdup(*argv++);
		begin = pfolder;
		while (--argc > 0)
		{
			if (!exists(*argv))
			{
				perror(*argv++);
				continue ;
			}
			if (!(pfolder->next = malloc(sizeof(t_folder))))
				exit(-1);
			pfolder = pfolder->next;
			pfolder->path = ft_strdup(*argv++);
			pfolder->next = NULL;
			pfolder->file = NULL;
		}
	}
	else
	{
		if (!(pfolder = malloc(sizeof(t_folder))))
			exit(-1);
		if (!(pfolder->path = malloc(sizeof(char) * 2)))
			exit(-1);
		begin = pfolder;
		pfolder->path[0] = '.';
		pfolder->path[1] = '\0';
		pfolder->file = NULL;
		pfolder->next = NULL;
	}
	return (begin);
}
