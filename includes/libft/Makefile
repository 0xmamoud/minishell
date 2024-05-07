# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:50:10 by kane              #+#    #+#              #
#    Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PRINTF_DIR = ./ft_printf/
PRINTF_SRC_DIR = $(PRINTF_DIR)src/
PRINTF_UTILS_DIR = $(PRINTF_DIR)utils/

SRC = ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\

BONUS = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

GNL = get_next_line.c\
	  get_next_line_utils.c\

PRINTF = $(PRINTF_SRC_DIR)ft_printf.c\
		 $(PRINTF_SRC_DIR)ft_parser.c\
		 $(PRINTF_SRC_DIR)ft_putptr.c\
		 $(PRINTF_SRC_DIR)ft_put_uint.c\
		 $(PRINTF_UTILS_DIR)ft_putchar.c\
		 $(PRINTF_UTILS_DIR)ft_putstr.c\
		 $(PRINTF_UTILS_DIR)ft_putnbr_base.c\

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS:.c=.o)

GNL_OBJ = $(GNL:.c=.o)

PRINTF_OBJ = $(PRINTF:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADERS = libft.h\
		 

all: $(NAME)

$(NAME): $(OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -include$(HEADERS) -o $@ -c $<

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

bonus: $(OBJ) $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
