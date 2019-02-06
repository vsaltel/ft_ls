/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/06 17:03:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct			s_option
{
	int				argc;
	int				l : 1;
	int				rec : 1;
	int				a : 1;
	int				r : 1;
	int				t : 1;
	int				f : 1;
}						t_option;

typedef struct			s_file
{
	struct stat		pstat;
	char			*path;
	char			*name;
	char			*mode;
	char			extand_perm;
	int				nlink;
	char			*owner;
	char			*group;
	int				bytes;
	int				major;
	int				minor;
	char			*date;
	char			*path_link;
}						t_file;

typedef struct			s_folder
{
	char			*path;
	int				nb_file;
	long long		total_blocks;
	t_file			*file;
	struct s_folder	*next;
}						t_folder;

void					pexit(char *str);
t_folder				*malloc_pfolder(char *path);
t_folder				*parse_options(t_folder *pfolder,
						t_option *option, int argc, char **argv);
void					fill_list(t_folder *pfolder, t_option option);
void					test_folder(char **argv, int argc);
char					*str_withoutpath(char *str);
void					sort_ascii(t_folder *pfolder);
void					sort_time(t_folder *pfolder);
void					display(t_folder *pfolder, t_option option);
t_folder				*select_dir(t_folder *pfolder,
							const t_folder *begin, t_option option);
void					set_stat(t_folder *pfolder, t_file *pfile);
void					memset_file(t_file *pfile);
void					memset_option(t_option *option);
void					free_folder(t_folder *pfolder, t_option option);
void					ell_option(t_folder *pfolder, t_file *pfile,
							t_option option);
int						can_open_folder(char *folder);
void					merge_sort(t_folder **list, t_option option);

#endif
