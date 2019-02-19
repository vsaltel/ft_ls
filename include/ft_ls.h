/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:07:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/02/19 17:49:19 by frossiny         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/acl.h>
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
	int				un : 1;
	int				arob : 1;
	int				c : 1;
	int				s : 1;
	int				g : 1;
	int				h : 1;
}						t_option;

typedef struct			s_file
{
	struct stat		pstat;
	char			*path;
	char			*name;
	char			*mode;
	char			extand_perm;
	char			**extp_tab;
	int				nlink;
	char			*owner;
	char			*group;
	long			bytes;
	int				major;
	int				minor;
	char			*date;
	char			*path_link;
	struct s_file	*next;
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
void					set_option(t_option *option, char *str);
int						exists(t_file *pfile, char *file, t_option options);
t_folder				*malloc_pfolder(char *path);
t_folder				*parse_options(t_folder *pfolder,
						t_option *option, int argc, char **argv);
void					test_folder(char **argv, int argc);
char					*str_withoutpath(char *str);
void					sort_ascii(char **tab);
void					display(t_folder *pfolder, t_option option, int isarg);
void					display_file(t_folder *pfolder, t_option option);
t_folder				*select_dir(t_folder *pfolder,
							const t_folder *begin, t_option option);
void					set_stat(t_folder *pfolder, t_file *pfile);
t_file					*memset_file(t_file *pfile);
void					memset_option(t_option *option);
void					free_folder(t_folder *pfolder, t_option option);
void					ell_option(t_folder *pfolder, t_file *pfile,
							t_option option);
int						can_open_folder(char *folder);
void					merge_sort_folder(t_folder **list, t_option option);
void					merge_sort_file(t_file **list, t_option option);
int						test_lawaccess(char *path, char *file);
int						*malloc_tab(size_t len);
t_file					*get_lstfile(t_file *files, size_t index);
char					*get_file_color(t_file *file, t_option option);

#endif
