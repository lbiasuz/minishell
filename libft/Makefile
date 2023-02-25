# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 21:23:55 by lbiasuz           #+#    #+#              #
#    Updated: 2023/01/31 10:00:18 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC_FILES	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_isupper.c ft_islower.c \
				ft_toupper.c ft_tolower.c \
				ft_calloc.c \
				ft_memchr.c ft_memcmp.c \
				ft_bzero.c ft_memset.c \
				ft_memcpy.c ft_memmove.c \
				ft_strlen.c \
				ft_strlcpy.c ft_strlcat.c \
				ft_strncmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_split.c \
				ft_striteri.c ft_strmapi.c \
				ft_strtrim.c \
				ft_atoi.c ft_itoa.c ft_itob.c ft_utoa.c ft_abs.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				ft_printf.c ft_printf_ultob.c ft_get_next_line.c \
				ft_get_next_line_utils.c

OUT_DIR		=	obj

OUT_FILES	=	$(SRC_FILES:%.c=$(OUT_DIR)/%.o)

HEAD_FILE	=	libft.h get_next_line.h ft_printf.h

COMPILER	=	gcc

OPTIONS		=	-Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OUT_FILES)
	ar rc $(NAME) $(OUT_FILES)

$(OUT_DIR)/%.o:	%.c
	mkdir -p $(OUT_DIR)
	$(COMPILER) $(OPTIONS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re bonus