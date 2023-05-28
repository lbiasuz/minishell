# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 21:15:56 by rmiranda          #+#    #+#              #
#    Updated: 2023/05/26 09:25:45 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_output.txt

TEST_INPUT = test_input.txt
SHASUM = "9ae3f7a48bcf5dff7e1c1b1f96cd99d0bd4b9732 Utest_output.txt"
TEST_SUBJECT = ../minishell

all: clean $(NAME)
	@echo $(SHASUM) | shasum -U -c
	@cp $(NAME) $(NAME)_old

$(NAME):
	@valgrind -s --leak-check=full --show-leak-kinds=all \
			--suppressions=../docs/readline.supp \
			--log-fd=9 ./$(TEST_SUBJECT)< $(TEST_INPUT) > $(NAME) 9>memcheck.log

clean:
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(NAME)_old

re: fclean all

shasum:
	@shasum -U $(NAME)

show:
	@cat $(NAME)

show_old:
	@cat $(NAME)_old

diff:
	@diff $(NAME) $(NAME)_old

.PHONY: all clean fclean re shasum show show_old diff

