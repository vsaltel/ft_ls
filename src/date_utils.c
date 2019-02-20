/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:59:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/20 17:35:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t	get_ftime(struct stat stats, t_option option)
{
	if (option.u)
		return (stats.st_atimespec.tv_sec);
	return (stats.st_mtimespec.tv_sec);
}

void	build_far_date(char *buf, time_t t)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = ctime(&t);
	ft_strncpy(buf, tmp + 4, 7);
	i = 7;
	j = 19;
	buf[i++] = ' ';
	while (tmp[j] == ' ')
		j++;
	while (ft_isdigit(tmp[j]))
	{
		buf[i++] = tmp[j++];
	}
	buf[i] = '\0';
}

char	*build_time(t_file *pfile, struct stat pstat, t_option option)
{
	char	buf[80];
	time_t	ftime;
	size_t	i;

	buf[0] = '\0';
	ftime = get_ftime(pstat, option);
	if (ftime + 15811200 < time(NULL) || ftime - 15811200 > time(NULL))
		build_far_date(buf, ftime);
	else
	{
		ft_strcpy(buf, ctime(&ftime) + 4);
		buf[12] = '\0';
	}
	return (ft_strdup(buf));
}
