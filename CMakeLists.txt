cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c includes/minishell.h src/command/command.c src/utils/utils.c src/args/arg.c src/errors/errors.c src/env/env.c src/builtins/echo.c src/env/env2.c src/parser/parser.c src/redirect/redirect.c src/builtins/builtins.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/libft/libft.a ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)