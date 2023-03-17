# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtins_cd_test.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 16:27:04 by rmiranda          #+#    #+#              #
#    Updated: 2023/03/16 23:29:08 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRCS PART 1 (BUILTINS)
BUILTINS_NAME = cd.a
BUILTINS_DIR = src/builtin
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
	@echo "\n\nFT_CD TESTING DONE"

test_1:
	@echo "\FT_CD:test:1 Next line should display: <--end"
	@./cd.a; echo "<--end"

test_2:
	@echo "\FT_CD:test:2 Next line should display: ft_cd chdir failed: No such file or directory(line_break)<--end"
	@./cd.a /wrong_mini_builtins; echo "<--end"

test_3:
	@echo "\FT_CD:test:3 Next line should display: <--end"
	@./cd.a /mini_builtins; echo "<--end"

.PHONY: all bonus clean fclean re