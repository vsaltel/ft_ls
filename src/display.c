/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:08:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/18 11:37:41 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	*espace(int *tab, t_folder *p, t_option option)
{
	t_file	*current;
	char	*tmp;

	if (!(tab = malloc_tab(4)))
		exit(-1);
	current = p->file;
	while (current)
	{
		if (tab[0] < ft_strlen(current->owner))
			tab[0] = ft_strlen(current->owner);
		if (tab[1] < ft_strlen(current->group))
			tab[1] = ft_strlen(current->group);
		tmp = ft_itoa(current->bytes);
		if (tab[2] < ft_strlen(tmp))
			tab[2] = ft_strlen(tmp);
		free(tmp);
		if (tab[2] < 8 && current->major)
			tab[2] = 8;
		tmp = ft_itoa(current->nlink);
		if (tab[3] < ft_strlen(tmp))
			tab[3] = ft_strlen(tmp);
		free(tmp);
		current = current->next;
	}
	return (tab);
}

static int	*colonne(int *tab, t_folder *p, t_option option)
{
	int				word_size;
	int				nb_file_a;
	t_file			*current;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (!(tab = malloc_tab(3)))
		exit(-1);
	word_size = 0;
	nb_file_a = 0;
	current = p->file;
	while (current)
	{
		if (word_size < ft_strlen(current->name))
			word_size = ft_strlen(current->name);
		current = current->next;
	}
	tab[0] = word_size + 1;
	tab[1] = w.ws_col / tab[0];
	tab[2] = p->nb_file / tab[1];
	if (p->nb_file % tab[1])
		tab[2]++;
	return (tab);
}

static void	display_col(t_folder *p, int *tab, t_option option, int isarg)
{
	int		i;
	int		l;
	int		c;
	t_file	*file;

	l = 0;
	while (l < tab[2])
	{
		i = 0;
		c = 0;
		while (i + l < p->nb_file && c <= tab[1])
		{
			file = get_lstfile(p->file, i + l);
			if (file)
				ft_printf("%-*s", tab[0], file->name);
			i += tab[2];
			c++;
		}
		ft_putchar('\n');
		l++;
	}
}

static void	big_print(t_file *file, int *tab, t_option option)
{
	if (file->mode[0] == 'l')
		ft_printf("%s%-1c %*d %-*s  %-*s  %*d %s %s -> %s\n",
			file->mode, file->extand_perm, tab[3], file->nlink,
			tab[0], file->owner, tab[1], file->group,
			tab[2], file->bytes, file->date,
			file->name, file->path_link);
	else if (file->mode[0] == 'c' || file->mode[0] == 'b')
		ft_printf("%s%-1c %*d %-*s  %-*s  %*d, %3d %s %s\n",
			file->mode, file->extand_perm, tab[3], file->nlink,
			tab[0], file->owner, tab[1], file->group,
			tab[2] - 5 >= 0 ? tab[2] - 5 : 0, file->major,
			file->minor, file->date, file->name);
	else
		ft_printf("%s%c %*d %-*s  %-*s  %*d %s %s\n",
			file->mode, file->extand_perm, tab[3], file->nlink,
			tab[0], file->owner, tab[1], file->group,
			tab[2], file->bytes, file->date, file->name);
}

void		display(t_folder *p, t_option option, int isarg)
{
	int		*tab;
	t_file	*current;

	tab = NULL;
	if (option.l)
	{
		if (p->file && !isarg)
			ft_printf("total %lld\n", p->total_blocks);
		tab = espace(tab, p, option);
	}
	else
		tab = colonne(tab, p, option);
	if ((!option.l && !option.un) || option.c)
		display_col(p, tab, option, isarg);
	else
	{
		current = p->file;
		while (current)
		{
			option.l ? big_print(current, tab, option) :
				ft_printf("%s\n", current->name);
			current = current->next;
		}
	}
	free(tab);
}
