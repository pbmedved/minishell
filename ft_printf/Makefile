# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iadrien <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 15:39:57 by iadrien           #+#    #+#              #
#    Updated: 2020/07/15 16:35:00 by iadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c utils.c parse_num.c print_functions_1.c \
prefix_func.c get_specs.c ft_atoi.c ft_isdigit.c \
ft_strchr.c ft_strlen.c ft_tolower.c ft_toupper.c

OBJ = $(SRC:.c=.o)

all: libftprintf.a

bonus: all

libftprintf.a: $(OBJ) ft_printf.h
	ar rc libftprintf.a $(OBJ)
	ranlib libftprintf.a

%.o: %.c ft_printf.h
	gcc -c -Wall -Wextra -Werror $<

re: fclean libftprintf.a

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f libftprintf.a