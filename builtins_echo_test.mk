# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtins_echo_test.mk                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 16:27:04 by rmiranda          #+#    #+#              #
#    Updated: 2023/03/01 20:53:15 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRCS PART 1 (BUILTINS)
BUILTINS_NAME = echo.a
BUILTINS_DIR = mini_builtins
BUILTINS_SRCS = $(BUILTINS_DIR)/$(BUILTINS_NAME:%.a=%.c)
BUILTINS_INCLUDES = libft/libft.h

# LIBFT
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = libft/

# OTHER
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc $(CFLAGS)
RM = rm -rf


all: $(LIBFT) $(BUILTINS_NAME)


$(BUILTINS_NAME): $(BUILTINS_SRCS) $(BUILTINS_INCLUDES)
	$(CC) $(CFLAGS) -o $@  $< -L$(LIBFT_PATH) -lft

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) clean

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(BUILTINS_NAME)

re: fclean all

test: all test_1 test_2 test_3
	@echo "\n\nECHO TESTING DONE"

test_1:
	@echo "\nEcho:test:1 Next line should display: Hello World! 0\n<--end"
	@./echo.a Hello World! $$?; echo "<--end"

test_2:
	@echo "\nEcho:test:2 Next line should display: Hello World! 0<--end"
	@./echo.a -n Hello World! $$?; echo "<--end"

test_3:
	@echo "\nEcho:test:3 Next line should display: 0<--end"
	@./echo.a -n $$?; echo "<--end"

.PHONY: all bonus clean fclean re