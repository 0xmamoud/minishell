# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 16:40:58 by tbarret           #+#    #+#              #
#    Updated: 2024/04/04 13:45:09 by tbarret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/parsing/main.c
OBJ = ${SRC:.c=.o}
NAME = minishell
HEADER  = include
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: ${NAME}

%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	@make -C include/libft
	${CC} ${CFLAGS} ${OBJ} -I ${HEADER} -o ${NAME}  -L include/libft -lft

clean:
	@make -C include/libft clean
	${RM} ${OBJ}

fclean: clean
	@make -C include/libft fclean
	${RM} ${NAME}

bonus: all

re: fclean all

.PHONY : all clean fclean re