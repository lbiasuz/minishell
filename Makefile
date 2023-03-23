# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 16:42:17 by rmiranda          #+#    #+#              #
#    Updated: 2023/03/23 20:27:10 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
OPT		=	-Wall -Werror -Wextra -g3
# PATH
PATH_NAME		=	src
PATH_BUILTINS	=	$(PATH_NAME)/builtins
PATH_OBJ		=	obj
PATH_INCLUDE	=	include
# SRC
SRC				+=	$(PATH_NAME)/minishell.c
SRC				+=	$(PATH_NAME)/bin_path.c
SRC				+=	$(PATH_NAME)/env.c
SRC				+=	$(PATH_NAME)/helper.c
SRC				+=	$(PATH_NAME)/redirect.c
SRC				+=	$(PATH_NAME)/runner.c
SRC				+=	$(PATH_BUILTINS)/cd.c
SRC				+=	$(PATH_BUILTINS)/echo.c
SRC				+=	$(PATH_BUILTINS)/env.c
SRC				+=	$(PATH_BUILTINS)/export.c
SRC				+=	$(PATH_BUILTINS)/pwd.c
SRC				+=	$(PATH_BUILTINS)/unset.c
# OBJ
OBJ				=	$(SRC:%.c=$(PATH_OBJ)/%.o)
# INCLUDES
INCLUDES		+=	$(PATH_INCLUDE)/minishell.h
INCLUDES		+=	$(PATH_INCLUDE)/env.h
INCLUDES		+=	$(PATH_INCLUDE)/redirect.h
DEP				=	libft.a

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	$(CC) $(OPT) $(OBJ) $(DEP) -lreadline -o $(NAME)

$(PATH_OBJ)/%.o: %.c $(INCLUDES)
	mkdir -p $(dir $@)
	$(CC) $(OPT) -c $< -o $@

$(DEP):
	@mkdir -p $(PATH_OBJ)
	make -C libft/ all
	mv libft/libft.a libft.a

clean:
	make -C libft/ clean
	rm -rf $(PATH_OBJ)
	rm -f *.dSYM

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME) $(DEP)

re: fclean all

.PHONY: all clean fclean re bonus