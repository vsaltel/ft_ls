/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:13:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/01/28 09:23:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "ft_printf.h"

typedef struct			s_file
{
	char	*name;
	char	mode[11];
	char	*links;
	char	*owner;
	char	*group;
	char	*bytes;
	char	*date;
}						t_file;

#endif