/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/24 15:31:55 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void 			preallocated(t_vars *vars)
{
	if (!(vars->buff = ft_calloc(1,1)))
		exit_error("Malloc error\n", errno);
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
}

int				check_end(t_parse *parse, char c)
{
	if (ft_strchr(" |;<>", c))
	{
		if (parse->brack || parse->brack_2)
			return (1);
		else
			return (0);
	}
	return (1);
}
int				check_end_arg(t_parse *parse, char c) {
	if (ft_strchr(" ;|", c)) {
		if (parse->brack || parse->brack_2)
			return (1);
		else
			return (0);
	}
	return (1);
}

char			*str_parser(char *buff, int *n, t_command *comm)
{
	t_parse 	parse;
	int			i;
	t_args 		*arg;

	i = 0;
	parse.brack = 0;
	parse.brack_2 = 0;

//	while (check_end_arg(&parse, buff[i]))
	while (buff[i])
	{
		arg = arg_new();
		while(buff[i] == ' ')
			i++;
		if (buff[i] && buff[i] == '\'' && !parse.brack_2)
		{
			parse.brack = parse.brack ? 0 : 1;
			i++;
		}
		else if (buff[i] && buff[i] == '"' && !parse.brack)
		{
			parse.brack_2 = parse.brack_2 ? 0 : 1;
			i++;
		}
		else
			arg->arg = str_reallocpy(arg->arg, buff[i++]);
	}
	arg_add(&comm->args, arg);
}

int				set_state(t_args *args, char *buff)
{
	int i;

	i = 1;
	if (*buff == '|' )
		args->state = 2;
	else if (*buff == '>' && buff[i] != '>' )
		args->state = 3;
	else if (*buff == '<' )
		args->state = 4;
	else if (*buff == '>' && buff[i++] == '>')
		args->state = 5;
	else if (*buff == '$')
		args->state = 6;
	return (i);
}

int				set_bracks(t_parse *prs, char c)
{
	if (c == '"')
	{
		prs->brack_2 = prs->brack_2 ? 0 : 1;
		if (prs->brack)
			return (0);
		return (1);
	}
	else if (c == '\'')
	{
		prs->brack = prs->brack ? 0 : 1;
		if (prs->brack_2)
			return (0);
		return (1);
	}
	return (1);
}

int 			brack_status(t_parse *prs)
{
	if (prs->brack_2 || prs->brack)
		return (1);
	return (0);
}



void			parse_bracks(t_command *comm, t_parse *prs, char c)
{
	if (!set_bracks(prs, c))
		comm->command = str_reallocpy(comm->command, c);
	prs->i++;
}

void 			parse_escape(t_command *comm, t_parse *prs, char *buff) {
	if (brack_status(prs))
	{
		comm->command = str_reallocpy(comm->command, '\\');
		prs->i++;
	}
	else
	{
		comm->command = str_reallocpy(comm->command, buff[prs->i + 1]);
		prs->i += 2;
	}
}

int				command_write(t_command *comm, char *buff)
{
	t_parse prs;

	prs = (t_parse){0,0, 0, 0};
	while(buff[prs.i] && check_end(&prs, buff[prs.i]))
	{
		if (buff[prs.i] == '"' || buff[prs.i] == '\'')
			parse_bracks(comm, &prs, buff[prs.i]);
		else if (buff[prs.i] == '\\')
			parse_escape(comm, &prs, buff);
		else
			comm->command = str_reallocpy(comm->command, buff[prs.i++]);
	}
	return (prs.i);
}

void			parse_bracks_arg(t_args *args, t_parse *prs, char c)
{
	if (!set_bracks(prs, c))
		args->arg = str_reallocpy(args->arg, c);
	prs->i++;
}

void 			parse_escape_arg(t_args *args, t_parse *prs, char *buff) {
	if (brack_status(prs))
	{
		args->arg = str_reallocpy(args->arg, '\\');
		prs->i++;
	}
	else
	{
		args->arg = str_reallocpy(args->arg, buff[prs->i + 1]);
		prs->i += 2;
	}
}

void 	parse_dollar_arg(t_args *args, t_parse *prs, char *buff, t_env *env)
{
	char *new;
	int valid;

	valid = 0;
	if (!(new = ft_calloc(1,1)))
		exit_error("Calloc error", errno);
	if (prs->brack && !prs->brack_2)
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
	else
	{
		prs->i++;
		if (!ft_isalpha(buff[prs->i]))
		{
			valid = 1;
			prs->i++;
		}
		while (ft_isalnum(buff[prs->i]))
			new = str_reallocpy(new, buff[prs->i++]);
		if (valid)
			args->arg = str_reallocpy_str(args->arg, new);
		else
			args->arg = str_reallocpy_str(args->arg, env_take(env, new));
	}
	free(new);
}

int 			parse_semicolon(t_args *args, t_parse *prs, char *buff)
{
	if (brack_status(prs))
	{
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
		return (0);
	}
	else
	{
		if (buff[prs->i] == ';')
			args->state = 7;
		else
			args->state = 8;
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
		return  (1);
	}
}

int				arg_write(t_env *env, t_args *args, char *buff)
{
	t_parse prs;

	prs = (t_parse){0,0, 0, 0};
	while(buff[prs.i] && check_end(&prs, buff[prs.i])) {
		if (buff[prs.i] == '"' || buff[prs.i] == '\'')
			parse_bracks_arg(args, &prs, buff[prs.i]);
		else if (buff[prs.i] == '\\')
			parse_escape_arg(args, &prs, buff);
		else if (buff[prs.i] == '$')
			parse_dollar_arg(args, &prs, buff, env);
		else if (buff[prs.i] == ';' || buff[prs.i] == '|')
		{
			if (parse_semicolon(args, &prs, buff))
				return (prs.i);
		}
		else
			args->arg = str_reallocpy(args->arg, buff[prs.i++]);
	}
	return (prs.i);
}

int				old_arg_write(t_args *arg, const char *buff)
{
	int i;
	t_parse prs;
	prs.brack_2 = 0;
	prs.brack = 0;

	i = 0;
	if (buff[i] == ';' && !prs.brack && !prs.brack_2)
	{
		arg->state = 7;
		arg->arg = str_reallocpy(arg->arg, buff[i++]);
		return (i);
	}
	else if (buff[i] == '|' && !prs.brack && !prs.brack_2)
	{
		arg->state = 8;
		arg->arg = str_reallocpy(arg->arg, buff[i++]);
		return (i);
	}
	while (buff[i] && check_end(&prs, buff[i]))
	{
		if (buff[i] == '"' || buff[i] == '\'')
		{
			if (!set_bracks(&prs, buff[i]))
				arg->arg = str_reallocpy(arg->arg, buff[i++]);
			else
				i++;
		}
		else if (buff[i] == '\\' && buff[i+1] == ' ' && !prs.brack && !prs.brack_2)
		{
			arg->arg = str_reallocpy(arg->arg, ' ');
//			i++;
		}
		else if (buff[i] == '$' && !prs.brack)
		{
			arg->state = 6;
			arg->arg = str_reallocpy(arg->arg, buff[i++]);
		}
		else
			arg->arg = str_reallocpy(arg->arg, buff[i++]);
	}
	return (i);
}

int 			old_command_write(t_command *comm, const char *buff) {
	int i;

	i = 0;
	while (buff[i] == ' ')
		i++;
	while (buff[i] && buff[i] != ' ' && buff[i] != ';' && buff[i] != '|')
	{
		comm->command = str_reallocpy(comm->command, buff[i]);
		i++;
	}
	return (i);

}

int 			pipe_write(t_args *args, char *buff)
{
	while (*buff && ft_strchr(";|", *buff))
	{
		args->arg = str_reallocpy(args->arg, *buff);
		if(*buff == ';')
			args->state = 7;
		else if (*buff == '|')
			args->state = 8;
		else if (*buff == '>' && buff[1] != '>' )
			args->state = 3;
		else if (*buff == '<')
			args->state = 4;
		else if (*buff == '>' && buff[1] == '>')
		{
			args->state = 5;
			return (2);
		}
		else if (*buff == '<' && buff[1] == '<')
		{
			args->state = 4;
			return (2);
		}
		buff++;
//		return (1);
	}
	return (ft_strlen(args->arg));
}


void			buff_parser(t_vars *vars, char *buff)
{
	t_command 	*new_comm;
	t_args		*new_arg;

	while (*buff)
	{
		new_comm = command_new();
		buff += command_write(new_comm, buff);
		buff += whitespace_remove(buff);
		while (*buff && *buff != ' ')
		{
			if (ft_strchr(";|", *buff))
			{
				new_arg = arg_new();
				buff += pipe_write(new_arg, buff);
				arg_add(&new_comm->args, new_arg);
				buff += whitespace_remove(buff);
				break;
			}
			new_arg = arg_new();
			buff += arg_write(vars->env, new_arg, buff);
			arg_add(&new_comm->args, new_arg);
			buff += whitespace_remove(buff);
		}
		command_add(&vars->comm, new_comm);
	}
}

void 			print_by_state(char *s, t_args *args, t_vars *vars)
{
	if (args && args->next)
	{
		if (args->state == 1 || args->state == 6)
			ft_printf("%s", s);
		else if (args->state == 3)
			write_in_file(s, args->next);
		else if (args->state == 5)
			save_write_in_file(s, args->next);
	}
	else if (s)
		ft_putstr_fd(s, 1);
}
void 			exit_handler(t_command *comm)
{
	if (comm->args)
		exit(ft_atoi(comm->args->arg));
	exit(0);
}

char			*take_env_by_arg(t_vars *vars, char *s)
{
	char *key;
	char *new_s;
	char *value;
	int 	i;

	i = 0;
	new_s = NULL;
	key = NULL;

	while(s[i])
	{
		if (s[i] == '$')
		{
			i++;
			while (s[i] && s[i] != ' ')
				key = str_reallocpy(key, s[i++]);
			value = env_take(vars->env, key);
			new_s = str_reallocpy_str(new_s, value);
			key = NULL;
		}
		else
			new_s = str_reallocpy(new_s, s[i++]);
	}
	return (new_s);

}

char 			*get_str_by_state(t_args *args)
{
	if (args->state == 3)
		return (">");
	if (args->state == 4)
		return ("<");
	if (args->state == 5)
		return (">>");
	return (0);

}
void 		call_extern_prog(t_command *comm, char *prog, char **envp)
{
	char **ar;
	t_args *arg;
	pid_t pid;
	int d;
	int i;
	int fd;

	i = 0;
	arg = comm->args;
	if (!(ar = malloc((arg_count(comm) + 2) * sizeof(char *))))
		exit_error("Malloc error", 1);
	ar[i++] = prog;
	while (arg && arg->state == 1)
	{
		ar[i++] = arg->arg;
		arg = arg->next;
	}
	ar[i] = NULL;
	pid = fork();
	if (!pid)
	{
		if (arg && arg->state == 3 && arg->next)
		{
			fd = open(arg->next->arg, O_CREAT | O_TRUNC | O_RDWR, 0644);
			dup2(fd,1);
			execve(prog, ar, envp);
		}
		else if (arg && arg->state == 5 && arg->next)
		{
			fd = open(arg->next->arg,  O_CREAT | O_APPEND | O_RDWR, 0644);
			dup2(fd,1);
			execve(prog, ar, envp);
		}
		else
			execve(prog, ar, envp);
	}
	else if (pid < 0)
		exit_error("fork error",1);
	else
		waitpid(pid,&d,0);

}


char		*try_find_prog(char *name, t_vars *vars)
{
	char 	*path;
	char 	*add;
	int		fd;
	int 	i;

	i = 0;
	add = ft_calloc(1, 1);
	path = env_take(vars->env, "PATH");
	while (*path)
	{
		if ((fd = open(add, O_RDONLY)) > 0)
		{
			close(fd);
			return (add);
		}
		ft_bzero(add,ft_strlen(add));
		while (*path && *path != ':')
			add = str_reallocpy(add, *path++);
		add = str_reallocpy(add, '/');
		path++;
		while (name[i])
			add = str_reallocpy(add, name[i++]);
		i = 0;
	}
	close(fd);
	return (NULL);
}

void		executable(t_command *comm, t_vars *vars, char **envp)
{
	char 	*path;

	path = try_find_prog(comm->command, vars);
	if (path)
		call_extern_prog(comm, path, envp);
	else
		print_command_error(comm);
}
void 		echo_handler();
int			token_error(char *err)
{
	ft_putstr_fd("-bash: syntax error near unexpected token '", 2);
	write(2, err, ft_strlen(err));
	write(2, "'\n", 2);
	return (0);
}

int			check_pipe(t_command *comm, t_args *arg)
{
	if (arg->next && arg->next->state == 8 && arg->arg[0] == '|')
	{
		if (arg->next->arg[0] == '|')
			return (token_error("||"));
		return (token_error("|"));
	}
	else
	{
		if (!comm->command[0])
			return (token_error("|"));
	}
}
int			check_semicolon(t_command *comm, t_args *arg)
{
	if (arg->next && arg->next->state == 7 && arg->arg[0] == ';')
	{
		if (arg->next->arg[0] == ';')
			return (token_error(";;"));
		return (token_error(";"));
	}
	else
	{
		if (!comm->command[0])
			return (token_error(";"));
	}
}

void 		which_token_err(char *buf)
{
	if (buf[0] == ';' && buf[1] == ';')
		token_error(";;");
	else if (buf[0] == ';' && buf[1] != ';')
		token_error(";");
	else if (buf[0] == '|' && buf[1] == '|')
		token_error("||");
	else
		token_error("|");
}

int			check_args(t_command *command)
{
	t_command 	*comm;
	t_args		*args;
	char *buf;

	comm = command;
	buf = NULL;
	while (comm)
	{
		args = comm->args;
		while (args)
		{
			if (args->state == 7 || args->state == 8) {
				if (ft_strlen(args->arg) == 1 && !comm->command[0])
					buf = str_reallocpy(buf, args->arg[0]);
				else if (ft_strlen(args->arg) > 1)
					buf = str_reallocpy_str(buf, args->arg);
			}
			args = args->next;
		}
		comm = comm->next;
	}
	if (!buf)
		return (1);
	which_token_err(buf);
	free(buf);
	return (0);
}

void 		ft_echo(t_command *comm) {
	t_args *arg;

	arg = comm->args;
	while (arg)
	{
		ft_putstr_fd(arg->arg, 1);
		arg = arg->next;
		if (arg)
			ft_putstr_fd(" ", 1);
		else
			ft_putchar_fd('\n', 1);
	}
}
void 		command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (!check_args(comm))
			break;
		if (!ft_strncmp_revers(comm->command, "echo", 4))
			ft_echo(comm);
		else if (!ft_strncmp(comm->command, "cd", 2))
			ft_cd(vars, comm);
		else if (!ft_strncmp(comm->command, "pwd", 3))
			ft_pwd(vars, comm);
		else if (!ft_strncmp(comm->command, "export", 6))
			ft_export(comm, vars);
		else if (!ft_strncmp(comm->command, "unset", 5))
			ft_unset(comm, vars);
		else if (!ft_strncmp(comm->command, "env", 3))
			env_print(vars->env);
		else if (!ft_strncmp(comm->command, "exit", 4))
			exit_handler(comm);
		else
			executable(comm, vars, envp);
		comm = comm->next;
	}
}

void 		print_promt(t_vars *vars)
{

	ft_putstr_fd(env_take(vars->env, "USER"), 1);
	write(1, "$ ", 2);
}


int			check_token_symb(char c)
{
	if (c == ';' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int			buff_check_token(char *buff)
{
	t_parse prs;
	int d;

	d = 0;
	prs = (t_parse){0,0,0, NULL};
	while (buff[prs.i])
	{
		if (check_token_symb(buff[prs.i])) {
			if (check_token_symb(buff[prs.i + 1])) {
				prs.new_s = str_reallocpy(prs.new_s, buff[prs.i]);
				prs.new_s = str_reallocpy(prs.new_s, buff[prs.i + 1]);
				which_token_err(prs.new_s);
				return 0;
			}
			if (!prs.i)
				which_token_err(prs.new_s = str_reallocpy(prs.new_s, buff[prs.i]));
			while (buff[prs.i] && buff[prs.i] == ' ')
				prs.i++;
			if (check_token_symb(buff[prs.i + 1])) {
				prs.new_s = str_reallocpy(prs.new_s, buff[prs.i]);
				prs.new_s = str_reallocpy(prs.new_s, buff[prs.i + 1]);
				which_token_err(prs.new_s);
				return 0;
			}
		}
		prs.i++;
	}
}

void		command_fix(t_command **comm)
{
	int i;
	t_command *res;

	res = *comm;
	while (res)
	{
		i = -1;
		while (res->command[++i])
			res->command[i] = (char)ft_tolower(res->command[i]);
		res = res->next;
	}
}
void 		command_getter(t_vars *vars, char **envp, char *s)
{
	char 	*promt;
	int 	byte;
	char 	b;

	b = 0;
	while(vars->state)
	{
		vars->buff = ft_calloc(1,1);
		print_promt(vars);
		while((byte = read(0,&b, 1)) && b != '\n')
			vars->buff = str_reallocpy(vars->buff, b);
//		if (!buff_check_token(vars->buff))
//			continue;
		buff_parser(vars, vars->buff);
		command_fix(&vars->comm);
		command_handler(vars->comm, vars, envp);
		dell_all_command(&vars->comm);
		free(vars->buff);
		vars->buff = NULL;
	}
}

int			main(int argc, char **argv, char **envp) {
	t_vars 	vars;
	char *buff;

	preallocated(&vars);
	env_save(&vars, envp);
	buff = NULL;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 2))
		buff = argv[2];
	command_getter(&vars, envp, buff);
	free(vars.buff);
	dell_all_env(&vars.env);
	return (0);
}
