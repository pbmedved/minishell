/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/21 13:27:14 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void 		preallocated(t_vars *vars)
{
	if (!(vars->buff = ft_calloc(1,1)))
		exit_error("Malloc error\n", errno);
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
}

int				check_end_arg(t_parse *parse, char c)
{
	if (ft_strchr(" |;", c))
	{
		if (parse->brack || parse->brack_2)
			return (1);
		else
			return (0);
	}
	return (1);
}
char			*str_parser(char *buff, int *n)
{
	t_parse 	parse;
	char *s;

	s = NULL;

	parse = (struct s_parse){0,0,0,NULL};
	parse.new_s = ft_calloc(1,1);
	while (buff[parse.i] && check_end_arg(&parse, buff[parse.i]))
	{
		if (ft_strchr("<>", buff[parse.i]) && !parse.brack_2 && !parse.brack)
		{
			*n = parse.i;
			return (parse.new_s);
		}
		if (buff[parse.i] == '\'')
		{
			parse.brack ? parse.brack-- : parse.brack++;
			parse.i++;
		}
		else if (buff[parse.i] == '"' && !parse.brack) {
			parse.brack_2 ? parse.brack_2-- : parse.brack_2++;
			parse.i++;
		}
		else if (buff[parse.i])
		{
			parse.i += buff[parse.i] == 92 && !parse.brack && !parse.brack_2 ? 1 : 0;
			parse.new_s = str_reallocpy(parse.new_s, buff[parse.i++]);
		}
	}
	*n = parse.i;
	return (parse.new_s);
}



/*
 * 				COMMAND STATE
 * 		;	1
 * 		|   2
 * 		>	3
 * 		<	4
 * 		>>	5

 */
int		set_state(t_args *args, char *buff)
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
void		buff_parser(t_vars *vars, char *buff)
{
	int n;

	t_command 	*new_comm;
	t_args		*new_arg;
	while (*buff)
	{
		while (*buff == ' ')
			buff++;
		new_comm = command_new();
		new_comm->command = str_parser(buff, &n);
		buff += n;
		while (*buff == ' ' || *buff == '\t')
			buff++;
		while (*buff && !ft_strchr("|;", *buff))
		{
			new_arg = arg_new();
			if (ft_strchr("<>$",*buff))
				buff += set_state(new_arg, buff);
			new_arg->arg = str_parser(buff, &n);
			arg_add(&new_comm->args,new_arg);
			buff += n;
			while (*buff == ' ')
				buff++;
		}
		buff += set_state(new_arg, buff);
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
		ft_printf("%s",s);
}

void 			exit_handler(t_command *comm)
{
	if (comm->args)
		exit(ft_atoi(comm->args->arg));
	exit(0);
}

void			env_del_one(t_env *del)
{
	if (del)
	{
		free(del->key);
		free(del->value);
		free(del);
		del = NULL;
	}
}

void 			echo_handler(t_command *command, t_vars *vars) {
	t_command 	*comm;
	t_args 		*arg;
	char 		*s;
	int 		i;
	int			n;

	n = 0;
	i = 0;
	if (!(s = ft_calloc(1, 1)))
		exit_error("Calloc error", 1);
	comm = command;
	arg = comm->args;
	while (arg && !ft_strncmp(arg->arg, "-n", 2))
	{
		n++;
		arg = arg->next;
	}
	if (!arg && !n)
		write(1,"\n",1);
	else if (!arg && n)
		return ;
	while (arg)
	{
		while (arg && (arg->state == 1))
		{
			while (arg->arg[i])
				s = str_reallocpy(s, arg->arg[i++]);
			if (arg->next)
				s = str_reallocpy(s, ' ');
			arg = arg->next;
			i = 0;
		}
		if (arg && arg->state == 6)
		{
			s = str_reallocpy_str(s, env_take(vars->env, arg->arg));
			arg = arg -> next;
		}

		if (!n)
			s = str_reallocpy(s, '\n');
		print_by_state(s, arg, vars);
		if (arg)
			arg = arg->next;
//		if (arg && arg->next && arg->next->next)
//			arg = arg->next->next;
	}
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
void 			call_extern_prog(t_command *comm, char *prog, char **envp)
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

void 		ft_pwd(t_vars *vars, t_command *command)
{
	char *pwd;

	pwd = env_take(vars->env, "PWD");

	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}

void 		env_add_or_change(t_env **env, char *key, char *value)
{
	t_env *res;
	t_env *new;

	res = env_take_ptr(*env, key);
	if (!res)
	{
		new = env_create();
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		env_add(env, new);
	}
	else
	{
		free(res->value);
		res->value = ft_strdup(value);
	}
}

void 		ft_cd(t_vars *vars, t_command *comm)
{
	char s[PATH_MAX];
	int		dir;
	if (!comm->args)
		dir = chdir(env_take(vars->env, "HOME"));
	else
		dir = chdir(comm->args->arg);
	if (dir == -1)
		exit_error("dir error", errno);
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars->env, "PWD"));
	getwd(s);
	env_add_or_change(&vars->env, "PWD", s);
}

void 		ft_export(t_command *comm, t_vars *vars)
{
	if (comm->args && comm->args->next)
		env_add_or_change(&vars->env, comm->args->arg, comm->args->next->arg);
}

void 		ft_unset(t_command *comm, t_vars *vars)
{
		if (comm->args)
			env_del_by_key(&vars->env, comm->args->arg);
}

void 		env_print(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env=env->next;
	}
}

void 		command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (!ft_strncmp_revers(comm->command, "echo", 4))
			echo_handler(comm, vars);
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
