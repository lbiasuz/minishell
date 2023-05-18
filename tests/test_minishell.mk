# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 21:15:56 by rmiranda          #+#    #+#              #
#    Updated: 2023/05/18 17:55:49 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_output.txt

TEST_INPUT = test_input.txt
SHASUM = "865162b873be653e8818f577fb4a312fe21013d3 Utest_output.txt"
TEST_SUBJECT = ../minishell

all: clean $(NAME)
	@echo $(SHASUM) | shasum -U -c
	@cp $(NAME) $(NAME)_old

$(NAME):
	@valgrind -s --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --trace-children=yes \
			--suppressions=../docs/readline.supp \
			./$(TEST_SUBJECT)< $(TEST_INPUT) > $(NAME)

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