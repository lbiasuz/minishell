# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 21:15:56 by rmiranda          #+#    #+#              #
#    Updated: 2023/04/04 20:23:34 by rmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_output.txt

TEST_INPUT = test_input.txt
TEST_HASH = "e3ab27789415f3a2baf354b4f7299ac68df62f35 Utest_output.txt"
TEST_SUBJECT = ../minishell

all: $(NAME)
	@echo $(TEST_HASH) | shasum -U -c
	@echo "Test output file created, please run with the "clean" command. Ortherwise"
	@echo 'you might need this: echo "$(NAME)" >> .gitignore'

$(NAME):
	@./$(TEST_SUBJECT) < $(TEST_INPUT) > $(NAME)

clean:
	rm -f $(NAME)

re: clean all

shasum: $(NAME)
	shasum -U $(NAME)

verbose: 
	./$(TEST_SUBJECT) < $(TEST_INPUT)
	@echo $(TEST_HASH) | shasum -U -c
	@echo "Test output file created, please run with the "clean" command. Ortherwise"
	@echo 'you might need this: echo "$(NAME)" >> .gitignore'

.PHONY: all shasum verbose