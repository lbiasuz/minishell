# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 15:31:09 by lbiasuz           #+#    #+#              #
#    Updated: 2023/02/26 16:11:04 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

OPTIONS = -Wall -Werror -Wextra

SRC_DIR = tests/

OBJ_DIR = tests/obj

DEP	=	libft.a

$(DEP):
	make -C libft/
	mv libft/libft.a libft.a

env_tests: $(DEP)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(OPTIONS) \
		$(SRC_DIR)/env_tests.c env.c env.h minishell.h $(DEP) \
		-o $(OBJ_DIR)/env_tests
	@./$(OBJ_DIR)/env_tests