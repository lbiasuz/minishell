NAME	=	test_minishell.a
SRC	+=	minishell_tester.c
SRC	+=	apply_test.c
INCLUDE	+=	minishell_tester.h
C_FLAGS	=	-g3 -Wall -Werror -Wextra
CC	=	gcc

OBJ	=	$(SRC:%.c=%.o)

all:	minishell.a $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJ) $(INCLUDE)

$(OBJ):	$(SRC) $(INCLUDE)
	$(CC) -c $(SRC) $(INCLUDE)

minishell.a:
	@echo Missing minishell executable

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
