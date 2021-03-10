cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c includes/minishell.h main.c 
src/command/command.c 
src/utils/utils.c 
src/args/arg.c 
src/errors/errors.c 
src/env/env.c 
src/builtins/echo.c 
src/env/env2.c 
src/parser/parser.c 
src/redirect/redirect.c 
src/builtins/builtins.c 
src/parser/parser2.c 
src/parser/parse3.c 
src/exec/execution.c 
src/exec/execution2.c 
src/command/command2.c 
src/builtins/exit.c 
src/signals/signals_handlers.c src/builtins/cd.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/libft/libft.a ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)