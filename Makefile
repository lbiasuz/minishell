# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 16:42:17 by rmiranda          #+#    #+#              #
#    Updated: 2023/04/04 19:26:43 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
OPT		=	-Wall -Werror -Wextra -g3

# PATHS
PATH_NAME		=	src
PATH_BUILTINS	=	$(PATH_NAME)/builtins
PATH_OBJ		=	obj
PATH_HEADERS	+=	include
PATH_HEADERS	+=	libft
PATH_LIBS		+=	libft

# FILES
SRC				+=	$(PATH_NAME)/bin_path.c
SRC				+=	$(PATH_NAME)/env.c
SRC				+=	$(PATH_NAME)/helper.c
SRC				+=	$(PATH_NAME)/minishell.c
SRC				+=	$(PATH_NAME)/parse.c
SRC				+=	$(PATH_NAME)/redirect.c
SRC				+=	$(PATH_NAME)/runner.c
SRC				+=	$(PATH_NAME)/token.c
SRC				+=	$(PATH_NAME)/dollar.c
SRC				+=	$(PATH_NAME)/signal_handler.c
SRC				+=	$(PATH_BUILTINS)/cd.c
SRC				+=	$(PATH_BUILTINS)/echo.c
SRC				+=	$(PATH_BUILTINS)/env.c
SRC				+=	$(PATH_BUILTINS)/export.c
SRC				+=	$(PATH_BUILTINS)/pwd.c
SRC				+=	$(PATH_BUILTINS)/unset.c
OBJ				=	$(SRC:%.c=$(PATH_OBJ)/%.o)
HEADER_FILES	=	$(foreach dir, $(PATH_HEADERS), $(wildcard $(dir)/*.h))
LIBS			+=	ft
LIBS			+=	readline
DEP				=	libft.a

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	$(CC) $(OPT) -o $(NAME) $(OBJ) $(PATH_HEADERS:%=-I%/) $(PATH_LIBS:%=-L%/) $(LIBS:%=-l%)

$(PATH_OBJ)/%.o: %.c $(HEADER_FILES)
	mkdir -p $(dir $@)
	$(CC) $(OPT) -c $< -o $@ $(PATH_HEADERS:%=-I%/)

$(DEP):
	@mkdir -p $(PATH_OBJ)
	make -C libft/ all

clean:
	make -C libft/ clean
	rm -rf $(PATH_OBJ)
	rm -f *.dSYM

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus