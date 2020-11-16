cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c includes/minishell.h src/parser/command/command.c src/utils/utils.c src/parser/args/arg.c src/errors/errors.c src/parser/env/env.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/libft/libft.a ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)