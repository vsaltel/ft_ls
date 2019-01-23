# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/16 11:23:33 by frossiny          #+#    #+#              #
#    Updated: 2019/01/23 15:22:32 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
#CFLAGS	+=	-Wall -Werror -Wextra
#CFLAGS = -g -fsanitize=address

NAME 	=	ft_ls
PRINTF	=	ft_printf
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs
FILES 	=	main.c
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

.PHONY: all clean fclean re $(PRINTF)

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(PRINTF) || $(MAKE) -C $(PRINTF)
	@echo "${_BLUE}${_BOLD}[Linking] $(NAME)${_END}"
	$(CC) $(CFLAGS) -o $(NAME) -L $(PRINTF) -lftprintf -I./$(INCDIR) -I./$(PRINTF)/include $(OBJS)
	@echo "${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR)/converters ] || mkdir -p $(OBJDIR)/converters
	@echo "${_PURPLE}Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I./$(INCDIR) -I./$(PRINTF)/include -o $@ -c $<

all: $(NAME)

clean:
	#@make -C $(LIBFT) clean
	@echo "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)

fclean: clean
	#@make -C $(LIBFT) fclean
	@echo "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)

re: fclean $(NAME)
