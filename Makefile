# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 22:40:53 by iadrien           #+#    #+#              #
#    Updated: 2020/12/02 00:01:49 by amayor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	main.c \
		includes/minishell.h \
		src/command/command.c \
		src/utils/utils.c \
		src/args/arg.c \
		src/errors/errors.c \
		src/env/env.c \
		src/builtins/echo.c \
		src/env/env2.c \
		src/parser/parser.c \
		src/redirect/redirect.c \
		src/builtins/builtins.c \
		src/parser/parser2.c \
		src/parser/parse3.c \
		src/exec/execution.c \
		src/exec/execution2.c \
		src/command/command2.c \
		src/builtins/exit.c

LIBFT_PATH = libft/libft.a
FT_PRINTF_PATH = ft_printf/libftprintf.a

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	$(MAKE) -C libft
	$(MAKE) -C ft_printf
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) $(LIBFT_PATH) $(FT_PRINTF_PATH)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	rm -f a.out