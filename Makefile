NAME	= minishell

CC 		= gcc-12

OPT		= -Wall -Werror -Wextra -g

SRC		= minishell.c

HEADER	= minishell.h

OBJ_DIR	= obj

OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

DEP	=	libft.a

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	$(CC) $(OPT) $(OBJ) $(DEP) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(OPT) -c $< -o $@

$(DEP):
	@mkdir -p $(OBJ_DIR)
	make -C libft/ all
	mv libft/libft.a libft.a

clean:
	make -C libft/ clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME) $(DEP)

re: fclean all

.PHONY:		all clean fclean re bonus