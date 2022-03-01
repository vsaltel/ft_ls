/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:29:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/21 14:12:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	disp_usage(char c)
{
	write(2, "ft_ls: illegal option -- ", 25);
	write(2, &c, 1);
	write(2, "\nusage: ft_ls [-CGRSaflrt1] [file ...]\n", 39);
	return (1);
}

static int	set_option_next(t_option *option, char c)
{
	if (c == 'l')
	{
		option->un = 0;
		option->l = 1;
		option->cc = 0;
		return (1);
	}
	else if (c == '1')
	{
		option->un = 1;
		option->l = 0;
		return (1);
	}
	else if (c == 'C')
	{
		option->cc = 1;
		option->l = 0;
		return (1);
	}
	else if (c == 'R')
	{
		option->rec = 1;
		return (1);
	}
	return (0);
}

static int	set_time_opt(t_option *option, char c)
{
	if (c == 't')
		return (option->t = 1);
	if (c == 'u')
		return (option->u = 1);
	if (c == 'U')
		return (option->cu = 1);
	if (c == 'c')
		return (option->c = 1);
	return (0);
}

void		set_option(t_option *option, char *str)
{
	size_t i;

	i = 0;
	while (str[++i])
		if (!set_option_next(option, str[i]) && !set_time_opt(option, str[i]))
		{
			if (str[i] == 'a')
				option->a = 1;
			else if (str[i] == 'r')
				option->r = 1;
			else if (str[i] == 'f')
				option->f = 1;
			else if (str[i] == 'S')
				option->s = 1;
			else if (str[i] == 'G')
				option->g = 1;
			else if (str[i] == 'A')
				option->ca = 1;
			else
				exit(disp_usage(str[i]));
		}
}
