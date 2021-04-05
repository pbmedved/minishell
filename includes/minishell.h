/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:04:25 by amayor            #+#    #+#             */
/*   Updated: 2021/04/05 22:52:30 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <stddef.h>

extern int				g_signal_flag;
extern char				*g_username;
extern int				g_r_code;

/*
** REDIRECT STATE
**    > 3
**    >> 4
**    <  5
*/

/*
** Определим статусы команды в зависимости от  наличия пайпа до, после, до И после
*/
#define					NO_PIPE 1
#define					PIPE_BEFORE_FLAG 4
#define					PIPE_AFTER_FLAG 3
#define					PIPE_AFT_BF_FLAG 34

typedef struct			s_exe {
	char				*prog;
	char				**ar;
}						t_exe;

typedef struct			s_parse {
	int					i;
	int					brack;
	int					brack_2;
}						t_parse;

typedef struct			s_args {
	char				*arg;
	int					state;
	struct s_args		*next;
}						t_args;

typedef struct			s_command {
	char				*command;
	int					state;
	int					fd_out;
	int					fd_in;
	struct s_args		*args;
	struct s_command	*next;
}						t_command;

typedef struct			s_env {
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_vars {
	t_env				*env;
	char				*buff;
	int					state;
	int					fd[2];
	char				*prompt;
	struct s_command	*comm;
	int					global_r_code;
}						t_vars;

/*
**		PARSER
*/
t_command				*command_new();
void					command_add(t_command **comm, t_command *new);
void					dell_all_command(t_command **command);
void					command_set_state(t_command *comm);
void					command_fix(t_command **comm);
void					command_getter(t_vars *vars, char **envp);
void					parse_dollar_comm(t_command *comm, t_parse *prs,
												char *buff, t_vars *vars);
void					command_set_fd_out(t_command *comm, char *file);
void					command_set_fd_in(t_command *comm, char *file);
void					input_handler(int res, char b, t_vars *vars);
t_args					*arg_new();
void					arg_add(t_args **arg, t_args *new);
int						take_last_args_arg(t_args *args);
void					dell_all_args(t_args **arg);
int						arg_count(t_command *comm);
int						check_pipes(t_command *command);

t_env					*env_create();
void					env_add(t_env **main, t_env *new);
void					env_save(t_vars *vars, char **envp);
char					*env_take(t_vars *vars, const char *key);
t_env					*env_take_ptr(t_env *env, const char *key);
void					dell_all_env(t_env **env);
void					env_del_by_key(t_env **env, char *key);
void					env_add_or_change(t_env **env, char *key, char *value);
void					env_del_one(t_env *del);
char					*take_env_by_arg(t_vars *vars, char *s);

/*
** 		REDIRECT
*/

void					save_write_in_file(char *s, t_args *arg);
void					write_in_file(char *s, t_args *arg);
/*
** 		UTILS
*/

char					*str_reallocpy(char *old, char c);
int						ft_strncmp_revers(char *in, char *this, size_t n);
char					*str_reallocpy_str(char *old, char *new);
int						whitespace_remove(char *s);
int						ft_strcmp(char *s1, char *s2);
int						ft_exists(char *name);
/*
** 		BUILTINS
*/

int						ft_export(t_command *comm, t_vars *vars);
int						ft_unset(t_command *comm, t_vars *vars);
int						env_print(t_env *env, char *prefix);
int						ft_cd(t_vars *vars, t_command *comm);
int						ft_pwd(void);
int						ft_echo(t_command *comm);
void					exit_handler(t_command *comm, t_vars *vars, t_exe *exe);

/*
** 		PARSER
*/

int						check_end(t_parse *parse, char c);
int						buff_parser_args(char *buff, t_args *args,
						t_vars *vars);
int						set_bracks(t_parse *prs, char c);
int						brack_status(t_parse *prs);
void					parse_bracks(t_command *comm, t_parse *prs, char c);
void					parse_escape(t_command *comm, t_parse *prs, char *buff);
int						command_write(t_command *comm, char *buff,
														t_vars *vars);
void					parse_bracks_arg(t_args *args, t_parse *prs, char c);
void					parse_escape_arg(t_args *args, t_parse *prs,
														char *buff);
void					parse_dollar_arg(t_args *args, t_parse *prs,
											char *buff, t_vars *vars);
void					parse_semicolon(t_args *args, t_parse *prs, char *buff);
int						parse_redirect(t_args *args, t_parse *prs, char *buff);
int						arg_write(t_vars *vars, t_args *args, char *buff);
int						pipe_write(t_args *args, char *buff, int pipe_flag);
void					buff_parser(t_vars *vars, char *buff, char **envp);
void					check_pipes_state_ch(t_args *args, t_command *comm,
															char **buf);
int						parse_dollar_arg_valid(t_vars *vars, t_args *args,
									t_parse *prs, char *buff);
int						buff_parser_command(char *buff, t_command *new_comm,
											t_vars *vars);

/*
** 		EXEC
*/

void					command_handler(t_command *comm, t_vars *vars,
														char **envp);
void					get_exe(t_command *comm, t_exe *exe, t_vars *vars);
void					clean_exe(t_exe *exe);
char					*try_find_prog(char *name, t_vars *vars);
int						try_recode(t_command *comm, t_vars *vars, t_exe *exe);
int						call_extern_prog(t_command *comm, char **envp,
														t_vars *vars);
int						call_extern_prog_pipe(t_command *comm, char **envp,
														t_vars *vars);

int						call_pipe_before_proc(t_command *comm, char **envp, t_vars *vars);
void					executable(t_command *comm, t_vars *vars, char **envp);
int						try_recode_prog(char *name);
int						check_redirect(t_command *command);

/*
** 		ERRORS
*/
int						check_token_symb(char c);
int						token_error(char *err);
void					which_token_err(char *buf);
void					exit_error(char *s, int err);
void					print_command_error(t_command *comm);
int						print_file_error(char *s);
int						export_error(char *key, char *value);
void					permission_error(char *prog, char *file);
void					newline_error(void);
int						no_home_error(void);
void					file_not_found(char *prog, char *file);
void					end_of_file_error(void);
void					to_many_args_error(void);

/*
** SIGNALS
*/

void					handler_sigint(int sig);
void					handler_sigquit(int sig);
#endif
