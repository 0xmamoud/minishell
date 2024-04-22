# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkane <mkane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 16:40:58 by tbarret           #+#    #+#              #
#    Updated: 2024/04/22 16:49:10 by mkane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
PARSING_DIR = src/parsing
REDIRECTION_DIR = src/redirection
BULTINS_DIR = src/bultins
UTILS_DIR = utils
OBJ_DIR = obj

HEADER = includes
CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline
RM = rm -rf

VAL_HIDE    := readline.hide
VAL_FLAGS    := --leak-check=full --show-leak-kinds=all -s --suppressions=$(VAL_HIDE)

SRC=\
	${SRC_DIR}/main.c\
	${PARSING_DIR}/washer.c\
	${PARSING_DIR}/tokenizer.c\
	${PARSING_DIR}/expender.c\
	${PARSING_DIR}/redirection.c\
	${PARSING_DIR}/replace.c\
	${BULTINS_DIR}/echo.c\
	${BULTINS_DIR}/env.c\
	${BULTINS_DIR}/exit.c\
	${BULTINS_DIR}/export.c\
	${BULTINS_DIR}/pwd.c\
	${BULTINS_DIR}/cd.c\
	${BULTINS_DIR}/unset.c\
	${BULTINS_DIR}/exec.c\
	${UTILS_DIR}/clear.c\
	${UTILS_DIR}/create_env.c\
	${UTILS_DIR}/lst_env.c\
	${UTILS_DIR}/lst_token.c\
	${UTILS_DIR}/token_utils.c\

OBJ = $(addprefix ${OBJ_DIR}/,$(notdir ${SRC:.c=.o}))

vpath %.c $(SRC_DIR) $(PARSING_DIR) $(UTILS_DIR) $(REDIRECTION_DIR) $(BULTINS_DIR)

all: ${NAME}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	@$(CC) ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	@make -C includes/libft
	${CC} ${CFLAGS} ${RLFLAGS} ${OBJ} -I ${HEADER} -o ${NAME} -L includes/libft -lft

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
