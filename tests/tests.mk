# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 15:31:09 by lbiasuz           #+#    #+#              #
#    Updated: 2023/03/16 23:32:04 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

OPTIONS = -Wall -Werror -Wextra -g3

SRC_DIR = tests/

OBJ_DIR = tests/obj

DEP	=	libft.a

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

$(DEP):
	@mkdir -p $(OBJ_DIR)
	make -C src/libft/
	mv src/libft/libft.a libft.a

env_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/env_tests.c src/env.c src/helper.c \
		include/env.h include/minishell.h $(DEP) \
		-o $(OBJ_DIR)/env_tests
	@$(VALGRIND) ./$(OBJ_DIR)/env_tests

export_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/export_tests.c src/builtin/export.c \
		src/env.c src/helper.c include/env.h include/minishell.h \
		$(DEP) -o $(OBJ_DIR)/export_tests
	@$(VALGRIND) ./$(OBJ_DIR)/export_tests USER=coder HELLO
	
unset_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/unset_tests.c \
		src/builtin/unset.c src/builtin/export.c \
		src/env.c src/helper.c include/env.h include/minishell.h \
		$(DEP) -o $(OBJ_DIR)/unset_tests
	@$(VALGRIND) ./$(OBJ_DIR)/unset_tests USER HELLO