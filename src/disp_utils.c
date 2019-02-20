/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:23:36 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/20 14:59:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_file_color(t_file *file, t_option option)
{
	char	*str;

	if (!isatty(1))
		return (ft_strdup(""));
	if (!option.g)
		return (ft_strdup("\033[34;37m"));
	if (S_ISBLK(file->pstat.st_mode))
		return (ft_strdup("\033[34;46m"));
	else if (S_ISCHR(file->pstat.st_mode))
		return (ft_strdup("\033[34;43m"));
	else if (S_ISDIR(file->pstat.st_mode))
		return (ft_strdup("\033[96m"));
	else if (S_ISLNK(file->pstat.st_mode))
		return (ft_strdup("\033[35m"));
	else if (S_ISSOCK(file->pstat.st_mode))
		return (ft_strdup("\033[32m"));
	else if (S_ISFIFO(file->pstat.st_mode))
		return (ft_strdup("\033[33m"));
	else if ((file->pstat.st_mode & (S_IXUSR)) ||
		(file->pstat.st_mode & (S_IXGRP)) || (file->pstat.st_mode & (S_IXOTH)))
		return (ft_strdup("\033[31m"));
	return (ft_strdup("\033[37m"));
}

void	print_col_file(t_file *file, t_option options, int col_width, int last)
{
	char	*color;

	if (!file)
		return ;
	color = get_file_color(file, options);
	if (!last)
		ft_printf("%s%s%s%*s", color, file->name, color[0] ? "\033[0m" : "",
			col_width - ft_strlen(file->name), " ");
	else
		ft_printf("%s%s%s", color, file->name, color[0] ? "\033[0m" : "");
	free(color);
}
