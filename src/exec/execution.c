/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:07:35 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/14 10:41:48 by amayor           ###   ########.fr       */
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
	if (name[0] == '.' && (fd = open(name, O_RDONLY)) > 0)
	{
		close(fd);
		return (ft_strdup(name));
	}
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
	// vars->global_r_code = 127;
	GLOBAL_R_CODE = 127;
	return (NULL);
}

int		try_recode(t_command *comm, t_vars **vars)
{
	errno = 0;
	if (!ft_strncmp_revers(comm->command, "echo", 4))
		return (ft_echo(comm, vars));
	else if (!ft_strncmp(comm->command, "cd", 2))
		return (ft_cd(vars, comm));
	else if (!ft_strncmp(comm->command, "pwd", 3))
		return(ft_pwd(vars, comm));
	else if (!ft_strncmp(comm->command, "export", 6))
		return(ft_export(comm, vars));
	else if (!ft_strncmp(comm->command, "unset", 5))
		return (ft_unset(comm, vars));
	else if (!ft_strncmp(comm->command, "env", 3))
		return (env_print((*vars)->env, vars));
	else if (!ft_strncmp(comm->command, "exit", 4))
		exit_handler(comm);
	return (0);
}

int			call_extern_prog(t_command *comm, char **envp, t_vars **vars)
{
	t_exe exe;
	pid_t pid;
	int fd [2];
	int	status = 0;

	pipe(fd);
//	dup2(comm->fd_out, 1);
	dup2(comm->fd_in, 0);
	get_exe(comm, &exe, *vars);
	if (exe.prog && !try_recode_prog(comm->command))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(comm->fd_out, 1);
			execve(exe.prog, exe.ar, envp);
			exit(0); // TODO: нужен ли этот exit если execve не возвращает управление при успешном выполнении
		}
		else
		{
//			dup2(comm->fd_in, 0);
			// wait(&pid);
			waitpid(pid, &status, WUNTRACED);
			if (WIFEXITED(status) != 0)
				// (*vars)->global_r_code = WEXITSTATUS(status);
				GLOBAL_R_CODE = WEXITSTATUS(status);
				// printf("status from waitpid = %d\n", WEXITSTATUS(status));
			// exit(0);
			// close(fd[1]);
		}
	}
	else
		try_recode(comm, vars);
	clean_exe(&exe);
//	close(comm->fd_out);
//	close(comm->fd_in);
	return 1;
}

int		call_extern_prog_pipe(t_command *comm, char **envp, t_vars **vars)
{
	t_exe exe;
	pid_t pid;
	int fd [2];

	get_exe(comm, &exe, *vars);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
//		dup2(fd[1], 1);
//		if (comm->fd_out > 1)
		dup2(comm->fd_out, 1);
		dup2(fd[1], comm->fd_out);
		close(fd[0]);
		if (!try_recode(comm, vars))
			execve(exe.prog, exe.ar, envp);
		close(fd[1]);
		exit(1);
	}
	else
	{
//		dup2(fd[0], 0);
		dup2(fd[0], comm->fd_in);
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

void		executable(t_command *comm, t_vars **vars, char **envp)
{
		if (comm->state == 3)
			call_extern_prog_pipe(comm, envp, vars);
		else
			call_extern_prog(comm, envp, vars);
}

