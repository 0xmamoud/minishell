# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkane <mkane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 16:40:58 by tbarret           #+#    #+#              #
#    Updated: 2024/04/17 14:32:59 by mkane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
PARSING_DIR = src/parsing
UTILS_DIR = utils
OBJ_DIR = obj
HEADER = includes
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

VAL_HIDE    := readline.hide
VAL_FLAGS    := --leak-check=full --show-leak-kinds=all -s --suppressions=$(VAL_HIDE)

SRC=\
	${SRC_DIR}/main.c\
	${PARSING_DIR}/washer.c\
	${UTILS_DIR}/clear.c\
	${UTILS_DIR}/env.c\
	${UTILS_DIR}/lst_env.c\

OBJ = $(addprefix ${OBJ_DIR}/,$(notdir ${SRC:.c=.o}))

vpath %.c $(SRC_DIR) $(PARSING_DIR) $(UTILS_DIR)

all: ${NAME}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	@make -C includes/libft
	${CC} ${CFLAGS} ${OBJ} -I ${HEADER} -o ${NAME} -L includes/libft -lft

val: $(NAME)
	valgrind $(VAL_FLAGS) ./$(NAME)

clean:
	@make -C includes/libft clean
	${RM} ${OBJ_DIR}

fclean: clean
	@make -C includes/libft fclean
	${RM} ${NAME}

bonus: all

re: fclean all

.PHONY : all clean fclean re
