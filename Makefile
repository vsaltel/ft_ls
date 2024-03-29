# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 14:37:18 by vsaltel           #+#    #+#              #
#    Updated: 2019/02/21 14:40:21 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	+=	-Wall -Werror -Wextra

NAME 	=	ft_ls
LIBFT	=	libft
SRCDIR	=	src
INCDIR	=	include
OBJDIR	=	objs
FILES 	=	ft_ls.c				\
			parser.c			\
			parser_flags.c		\
			display.c			\
			utils.c				\
			utils2.c			\
			l_option.c			\
			sort_folder.c		\
			sort_file.c			\
			free.c				\
			main.c				\
			tab_utils.c			\
			disp_utils.c		\
			date_utils.c
SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS 	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

##### Colors #####
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

.PHONY: all clean fclean re $(LIBFT)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -C $(LIBFT)
	@echo "${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft
	@echo "${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@echo "${_PURPLE}Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/include -o $@ -c $<

all: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@echo "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT) fclean
	@echo "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean $(NAME)
