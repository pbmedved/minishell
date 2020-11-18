/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/18 19:12:15 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"



void 		preallocated(t_vars *vars)
{
	if (!(vars->buff = ft_calloc(BUFF_SIZE, sizeof(char))))
		exit_error("Malloc error\n", errno);
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
}


char			*str_parser(char *buff, int *n)
{
	t_parse 	parse;

	parse = (struct s_parse){0,0,0,NULL};
	parse.new_s = ft_calloc(1,1);
	while (buff[parse.i] && (!ft_strchr(" |;", buff[parse.i])\
	|| parse.brack || parse.brack_2))
	{
		if (ft_strchr("<>", buff[parse.i]))
		{
			*n = parse.i;
			return (parse.new_s);
		}
		if (buff[parse.i] == '\'')
		{
			parse.brack ? parse.brack-- : parse.brack++;
			parse.i++;
		}
		else if (buff[parse.i] == '"' && !parse.brack)
		{
			parse.brack_2 ? parse.brack_2-- : parse.brack_2++;
			parse.i++;
		}
		else
		{
			parse.i += buff[parse.i] == 92 && !parse.brack ? 1 : 0;
			parse.new_s = str_reallocpy(parse.new_s, buff[parse.i++]);
		}
	}
	*n = parse.i;
	return (parse.new_s);
}



/*
 *
 * 				COMMAND STATE
 * 		;	1
 * 		|   2
 * 		>	3
 * 		<	4
 * 		>>	5
 *
 *
 *
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
		while (*buff == ' ')
			buff++;
		while (*buff && !ft_strchr("|;", *buff))
		{
			new_arg = arg_new();
			if (ft_strchr("<>",*buff))
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
//char 		*write_from_file(char *s, t_args *arg)
//{
//	int		fd;
//	char 	*new_s;
//	char	c;
//
//	if (!s || !arg)
//		exit_error("bad string",1);
//	if (!(fd = open(arg->arg, O_WRONLY)))
//		exit_error("bad file",1);
//	if (!(new_s = calloc(1,1)))
//		exit_error("Calloc error", 1);
//	while(read(fd, c, 1))
//	{
//		new_s = str_reallocpy(new_s, c);
//	}
//}
void		save_write_in_file(char *s, t_args *arg)
{
	int		fd;

	if (!s || !arg)
		exit_error("bad string",1);
	if (!(fd = open(arg->arg, O_CREAT | O_APPEND | O_RDWR, 0644)))
		exit_error("\"echo f\" hello", 1);
	if (arg->next && arg->next->state == 5)
		close(fd);
	else
	{
		ft_putstr_fd(s, fd);
		close(fd);
	}
}

void		write_in_file(char *s, t_args *arg)
{
	int		fd;

	if (!s || !arg)
		exit_error("bad string",1);
	if (!(fd = open(arg->arg, O_CREAT | O_TRUNC | O_RDWR, 0644)))
		exit_error("open problem", 1);
	if (arg->next && arg->next->state == 3)
		close(fd);
	else
	{
		ft_putstr_fd(s, fd);
		close(fd);
	}
}

void 		print_by_state(char *s, t_args *args, t_command *comm)
{
	if (args && args->next)
	{
		if (args->state == 1)
			ft_printf("%s", s);
		else if (args->state == 3)
			write_in_file(s, args->next);
		else if (args->state == 5)
			save_write_in_file(s, args->next);
	}
	else
		ft_printf("%s\n",s);
}
void 			echo_handler(t_command *command, t_vars *vars, char **envp) {
	t_command 	*comm;
	t_args 		*arg;
	char 		*s;
	int 		i;

	i = 0;
	if (!(s = ft_calloc(1, 1)))
		exit_error("Calloc eror", 1);
	comm = command;
	arg = comm->args;
	if (arg && !ft_strnstr(arg->arg, "-n", 2))
		s = str_reallocpy(s, '\n');
	else if (arg)
		arg = arg->next;
	while (arg)
	{
		while (arg && arg->state == 1)
		{
			while (arg->arg[i])
				s = str_reallocpy(s, arg->arg[i++]);
			s = str_reallocpy(s, ' ');
			arg = arg->next;
			i = 0;
		}
		print_by_state(s, arg, comm);
		if (arg && arg->next && arg->next->next)
			arg = arg->next->next;
	}
}

int 		arg_count(t_command *comm) {
	t_command *res;
	int i;

	i = 0;
	res = comm;
	while (res)
	{
		i++;
		res = res->next;
	}
	return (i);
}

void 		call_extern_prog(t_command *comm, char *prog, char **envp)
{
	char **ar;
	t_args *arg;
	pid_t pid;
	int i;

	i = 0;
	arg = comm->args;
	if (!(ar = malloc((arg_count(comm) + 2) * sizeof(char *))))
		exit_error("Malloc error", 1);
	ar[i++] = prog;
	while (arg)
	{
		ar[i++] = arg->arg;
		arg = arg->next;
	}
	ar[i] = NULL;
	if (!(pid = fork()))
		execve(prog, ar, envp);
}

int			ft_strncmp_revers(char *in, char *this, size_t n)
{
	size_t in_len;
	size_t this_len;

	in_len = ft_strlen(in) - 1;
	this_len = ft_strlen(this) - 1;
	while (n-- > 0)
	{
		if ((unsigned char)in[in_len] == '\0' || (unsigned char)this[this_len] == '\0' \
		|| ((unsigned char)in[in_len] != (unsigned char)this[this_len]))
		{
			if ((unsigned char)in[in_len] == (unsigned char)this[this_len])
				return (0);
			return ((unsigned char)in[in_len] - (unsigned char)this[this_len] > 0 ? 1 : -1);
		}
		in_len--;
		this_len--;
	}
	return (0);
}
char		*try_find_prog(char *name, t_vars *vars)
{
	char 	*path;
	char 	*add;
	int		fd;
	int 	i;

	i = 0;
	add = ft_calloc(1, 1);
	path = env_take(vars, "PATH");
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
	return (name);
}

void		executable(t_command *comm, t_vars *vars, char **envp)
{
	char 	*path;

	path = try_find_prog(comm->command, vars);
	if (path)
		call_extern_prog(comm, path, envp);



}



void 		command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (comm && !ft_strncmp_revers(comm->command, "echo", 4))
			echo_handler(comm, vars, envp);
		else if (comm && !ft_strncmp(comm->command, "cd", 2))
			ft_printf("cd");
		else if (comm && !ft_strncmp(comm->command, "pwd", 3))
			ft_printf("pwd");
		else if (comm && !ft_strncmp(comm->command, "export", 6))
			ft_printf("export");
		else if (comm && !ft_strncmp(comm->command, "unset", 5))
			ft_printf("unset");
		else if (comm && !ft_strncmp(comm->command, "env", 3))
			ft_printf("env");
		else if (comm && !ft_strncmp(comm->command, "exit", 4))
			ft_printf("exit");
		else
			executable(comm, vars, envp);
		comm = comm->next;
	}
}

void 		command_getter(t_vars *vars, char **envp)
{
	char *promt;

	promt = env_take(vars, "USER");
	for (int i = 0; i < 1; ++i)
	{
		ft_printf("%s$ ", promt);
		if (0 > read(1,vars->buff, BUFF_SIZE))
			exit_error("Read error\n", errno);
//		ft_strlcpy(vars->buff, "echo -n lol;echo -n kek", 200); // fix it!
		buff_parser(vars, vars->buff);
		command_handler(vars->comm, vars, envp);
		dell_all_command(&vars->comm);
		ft_bzero(vars->buff, BUFF_SIZE);

	}
}

int			main(int argc, char **argv, char **envp) {
	t_vars 	vars;
	char 	*s = argv[0];
	int d = argc;
	if (s) {
		preallocated(&vars);
		env_save(&vars, envp);
		command_getter(&vars, envp);
	}
	free(vars.buff);
	dell_all_env(&vars.env);
	return (0);
}
