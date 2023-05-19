# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 16:42:17 by rmiranda          #+#    #+#              #
#    Updated: 2023/05/19 10:26:52 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g3

# PATHS
PATH_NAME		=	src
PATH_BUILTINS	=	$(PATH_NAME)/builtins
PATH_OBJ		=	obj
PATH_HEADERS	+=	include
PATH_HEADERS	+=	libft
PATH_HEADERS	+=	/opt/local/include
PATH_LIBS		+=	libft
PATH_LIBS		+=	/opt/local/lib

# FILES
SRC				+=	$(PATH_NAME)/bin_path.c
SRC				+=	$(PATH_NAME)/cmd_build.c
SRC				+=	$(PATH_NAME)/dollar.c
SRC				+=	$(PATH_NAME)/env.c
SRC				+=	$(PATH_NAME)/helper.c
SRC				+=	$(PATH_NAME)/init.c
SRC				+=	$(PATH_NAME)/minishell.c
SRC				+=	$(PATH_NAME)/parse.c
SRC				+=	$(PATH_NAME)/redirect.c
SRC				+=	$(PATH_NAME)/runner.c
SRC				+=	$(PATH_NAME)/signal.c
SRC				+=	$(PATH_NAME)/table.c
SRC				+=	$(PATH_NAME)/token.c
SRC				+=	$(PATH_BUILTINS)/cd.c
SRC				+=	$(PATH_BUILTINS)/echo.c
SRC				+=	$(PATH_BUILTINS)/env.c
SRC				+=	$(PATH_BUILTINS)/exit.c
SRC				+=	$(PATH_BUILTINS)/export.c
SRC				+=	$(PATH_BUILTINS)/pwd.c
SRC				+=	$(PATH_BUILTINS)/unset.c
OBJ				=	$(SRC:%.c=$(PATH_OBJ)/%.o)
HEADER_FILES	+=	include/includes.h
HEADER_FILES	+=	include/defines.h
HEADER_FILES	+=	include/minishell.h
HEADER_FILES	+=	libft/ft_printf.h
HEADER_FILES	+=	libft/libft.h
LIBS			+=	ft
LIBS			+=	readline
LIBFT			=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(PATH_HEADERS:%=-I%/) $(PATH_LIBS:%=-L%/) $(LIBS:%=-l%)

$(PATH_OBJ)/%.o: %.c $(HEADER_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(PATH_HEADERS:%=-I%/)

$(LIBFT):
	make -C libft/ all

clean:
	make -C libft/ clean
	rm -rf $(PATH_OBJ)
	rm -f *.dSYM
	make -C tests -f test_minishell.mk clean

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)
	make -C tests -f test_minishell.mk fclean

re: fclean all

test: all
	make -C tests -f test_minishell.mk

valgrind: all
	valgrind -s --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --trace-children=yes \
			--suppressions=./docs/readline.supp \
			--log-fd=9 ./$(NAME)   9>memcheck.log

.PHONY: all clean fclean re test valgrind
