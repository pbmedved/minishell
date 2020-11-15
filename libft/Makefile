# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 15:11:46 by iadrien           #+#    #+#              #
#    Updated: 2020/05/28 14:17:58 by iadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_strlen.c ft_strlcpy.c \
ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strnstr.c ft_strncmp.c ft_atoi.c \
ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c \
ft_tolower.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c \
ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)


BONUS_OBJ = $(BONUS:.c=.o)


COMPILER_COMMAND = gcc
COMPILER_COMMAND_FLAGS = -c -Wall -Wextra -Werror
LIB_COMPILER_COMMAND = ar
LIB_COMPILER_COMMAND_FLAGS = rc

REMOVE_COMMAND = rm
REMOVE_COMMAND_FLAGS = -f
RANLIB = ranlib


all: $(NAME)

$(NAME): $(OBJ)
	$(LIB_COMPILER_COMMAND) $(LIB_COMPILER_COMMAND_FLAGS) $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

bonus: $(OBJ) $(BONUS_OBJ)
	$(LIB_COMPILER_COMMAND) $(LIB_COMPILER_COMMAND_FLAGS) $(NAME) $(OBJ) $(BONUS_OBJ)
	$(RANLIB) $(NAME)
	@touch bonus

%.o: %.c libft.h
	$(COMPILER_COMMAND) $(COMPILER_COMMAND_FLAGS) $<

clean:
	$(REMOVE_COMMAND) $(REMOVE_COMMAND_FLAGS) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(REMOVE_COMMAND) $(REMOVE_COMMAND_FLAGS) $(NAME) bonus

re: fclean all

.PHONY: OBJ BONUS_OBJ clean fclean all re

