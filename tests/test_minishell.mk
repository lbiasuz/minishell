# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 21:15:56 by rmiranda          #+#    #+#              #
#    Updated: 2023/04/17 21:16:43 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_output.txt

TEST_INPUT = test_input.txt
SHASUM = "c702604009017018e7ab546511fe04533d7edb1e Utest_output.txt"
TEST_SUBJECT = ../minishell

all: clean $(NAME)
	@echo $(SHASUM) | shasum -U -c
	@echo "Test output file created, please run with the "clean" command. Ortherwise"
	@echo 'you might need this: echo "$(NAME)" >> .gitignore'
	@cp $(NAME) $(NAME)_old

$(NAME):
	@./$(TEST_SUBJECT) < $(TEST_INPUT) > $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)_old

re: fclean all

shasum:
	shasum -U $(NAME)

show:
	@cat $(NAME)

show_old:
	@cat $(NAME)_old

diff:
	diff $(NAME) $(NAME)_old

.PHONY: all clean fclean re shasum show show_old diff