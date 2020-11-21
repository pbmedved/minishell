# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iadrien <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 22:40:53 by iadrien           #+#    #+#              #
#    Updated: 2020/11/20 11:19:31 by iadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c includes/minishell.h src/parser/command/command.c src/utils/utils.c src/parser/args/arg.c src/errors/errors.c src/parser/env/env.c \
libft/libft.a ft_printf/libftprintf.a

OBJ = $(SRC:.c=.o)
all: $(OBJ)
	$(MAKE) -C libft
	$(MAKE) -C ft_printf
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ)
clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	rm -f a.out