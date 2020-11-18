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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# define BUFF_SIZE 2048

typedef struct 	s_parse {
	int 		i;
	int 		brack;
	int 		brack_2;
	char 		*new_s;
}				t_parse;

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
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct 			s_vars {
	t_env				*env;
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



t_env 			*env_create();
void	 		env_add(t_env **main, t_env *new);
void			env_save(t_vars *vars, char **envp);
char			*env_take(t_vars *vars, const char *key);
void			dell_all_env(t_env **env);
/*
 * 		UTILS
 */

char			*str_reallocpy(char *old, char c);


/*
 * 		ERRORS
 */

void 	exit_error(char *s, int n);
#endif //MINISHELL_MINISHELL_H
