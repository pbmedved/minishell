//
// Created by Boris Medvedev on 15/11/2020.
//

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# define BUFF_SIZE 2048
typedef struct 			s_args {
	char				*arg;
	int 				state;
	struct s_args 		*next;
}						t_args;

typedef struct	 		s_command {
	char 				*command;
	int					state;
	struct s_args		*args;
	struct s_command	*next;
}						t_command;

typedef struct			s_env {
	char				*promt;
}						t_env;

typedef struct 			s_vars {
	t_env				env;
	char 				*buff;
	int					state; // 1 waiting; 0 EOF
	struct s_command	*comm;
}						t_vars;

/*
 * 		PARSER
 */
t_command		*command_new();
void 			command_add(t_command **comm, t_command *new);
void			dell_all_command(t_command **command);


t_args			*arg_new();
void 			arg_add(t_args **arg, t_args *new);
void			dell_all_args(t_args **arg);

/*
 * 		UTILS
 */

char			*str_reallocpy(char *old, char c);


/*
 * 		ERRORS
 */

void 	exit_error(char *s, int n);
#endif //MINISHELL_MINISHELL_H