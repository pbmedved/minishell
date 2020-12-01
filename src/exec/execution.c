/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:07:35 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/01 23:33:50 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*try_find_prog(char *name, t_vars *vars)
{
	char 	*path;
	char 	*add;
	int		fd;
	int 	i;

	i = 0;
	if ((fd = open(name, O_RDONLY)) > 0)
	{
		close(fd);
		return (ft_strdup(name));
	}
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

int		try_recode(t_command *comm, t_vars *vars)
{
	if (!ft_strncmp_revers(comm->command, "echo", 4))
		return (ft_echo(comm));
	else if (!ft_strncmp(comm->command, "cd", 2))
		return (ft_cd(vars, comm));
	else if (!ft_strncmp(comm->command, "pwd", 3))
		return(ft_pwd(vars, comm));
	else if (!ft_strncmp(comm->command, "export", 6))
		return(ft_export(comm, vars));
	else if (!ft_strncmp(comm->command, "unset", 5))
		return (ft_unset(comm, vars));
	else if (!ft_strncmp(comm->command, "env", 3))
		return (env_print(vars->env));
	else if (!ft_strncmp(comm->command, "exit", 4))
		exit_handler(comm);
	return 0;
}

int		call_extern_prog(t_command *comm, char **envp, t_vars *vars)
{
	t_exe exe;
	pid_t pid;
	int fd [2];

	pipe(fd);
	get_exe(comm, &exe, vars);
	if (exe.prog && !try_recode(comm, vars))
	{

		pid = fork();
		if (pid == 0) {
//			dup2(vars->fd[1], comm->fd_in);
			execve(exe.prog, exe.ar, envp);
			exit(1);
		} else {
//			dup2(vars->fd[0], comm->fd_out);
			wait(&pid);
		}
		clean_exe(&exe);
	}
	return 1;
}

int		call_extern_prog_pipe(t_command *comm, char **envp, t_vars *vars)
{
	t_exe exe;
	pid_t pid;
	int fd [2];

	get_exe(comm, &exe, vars);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], comm->fd_out);
		close(fd[0]);
		if (!try_recode(comm, vars))
			execve(exe.prog, exe.ar, envp);
		close(fd[1]);
		exit(1);
	}
	else
	{
		dup2(fd[0], comm->fd_out);
		close(fd[1]);
		wait(&pid);
		close(fd[0]);
	}
	clean_exe(&exe);
	return 1;
}
int 		ft_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1)
	{
		if (*s1++ != *s2++)
			return (0);
	}
	return (1);
}

int 		try_recode_prog(char *name)
{

	if (ft_strcmp("echo", name) || ft_strcmp("cd", name) \
	|| ft_strcmp("pwd", name) || ft_strcmp("export", name) \
	|| ft_strcmp("unset", name) || ft_strcmp("env", name) \
	|| ft_strcmp("exit", name))
		return (1);
	return (0);
}

void		executable(t_command *comm, t_vars *vars, char **envp)
{
//	char 	*path;
//
//	path = NULL;
//	if (try_recode_prog(comm->command))
//		path = ft_strdup(comm->command);
//	else
//		path = try_find_prog(comm->command, vars);
//	if (path)
//	{
		if (comm->state == 3)
			call_extern_prog_pipe(comm, envp, vars);
		else
			call_extern_prog(comm, envp, vars);
//	}
//	else
//		print_command_error(comm);
//	free(path);
}

