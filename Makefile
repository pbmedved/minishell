# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 22:40:53 by iadrien           #+#    #+#              #
#    Updated: 2020/12/11 22:01:18 by amayor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
COMPILER = clang
LIBS = -L$(LIBFT_PATH) -L$(FT_PRINTF_PATH) -lft -lftprintf
HEADER_DIR = includes
LIBFT_PATH = libft
FT_PRINTF_PATH = ft_printf
# OBJ_DIR = obj
SRC_FILES = 	main.c \
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
				src/builtins/exit.c \
				src/signals/signals_handlers.c

OBJ_FILES = $(SRC_FILES:.c=.o)


all: $(OBJ) $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -C libft
	@echo "Complile libft!"
	@$(MAKE) -C ft_printf
	@echo "Complile ft_printf!"
	$(COMPILER) $(CFLAGS) $(OBJ_FILES) -I $(HEADER_DIR) $(LIBS) -o $(NAME)

# $< - исходный файл
# $@ - целевой файл

# VPATH = src
# %.o: %.c
# 	@echo "** Compile obj files! **"
# 	$(COMPILER) $(FLAGS) -I $(HEADER_FILES_DIR) -c $^ -o $@

# $(OBJ_DIR):
# 	@mkdir $(OBJ_DIR)

clean:
	rm $(OBJ_FILES)
	# $(MAKE) -C libft clean
	# $(MAKE) -C ft_printf clean
	rm -f $(NAME)

re: clean all
