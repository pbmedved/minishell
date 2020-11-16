# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iadrien <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 22:40:53 by iadrien           #+#    #+#              #
#    Updated: 2020/11/16 16:37:43 by iadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c includes/minishell.h src/parser/command/command.c src/utils/utils.c src/parser/args/arg.c src/errors/errors.c libft/libft.a ft_printf/libftprintf.a

all:
	$(MAKE) -C libft
	$(MAKE) -C ft_printf
	gcc -Wall -Wextra -Werror $(SRC)
clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	rm -f a.out