# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 15:31:09 by lbiasuz           #+#    #+#              #
#    Updated: 2023/03/07 11:35:09 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

OPTIONS = -Wall -Werror -Wextra

SRC_DIR = tests/

OBJ_DIR = tests/obj

DEP	=	libft.a

$(DEP):
	@mkdir -p $(OBJ_DIR)
	make -C libft/
	mv libft/libft.a libft.a

env_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/env_tests.c env.c env.h minishell.h $(DEP) \
		-o $(OBJ_DIR)/env_tests
	@ valgrind ./$(OBJ_DIR)/env_tests

export_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/export_tests.c mini_builtins/export.c env.c env.h minishell.h \
		$(DEP) -o $(OBJ_DIR)/export_tests
	@valgrind .
	
unset_tests: $(DEP)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/unset_tests.c \
		mini_builtins/unset.c mini_builtins/export.c \
		env.c env.h minishell.h \
		$(DEP) -o $(OBJ_DIR)/unset_tests
	@valgrind ./$(OBJ_DIR)/unset_tests USER