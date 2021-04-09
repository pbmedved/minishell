/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:07:35 by iadrien           #+#    #+#             */
/*   Updated: 2021/04/08 23:23:06 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*try_find_prog(char *name, t_vars *vars)
{
	char	*path;
	char	*add;

	if (ft_exists(name))
		return (ft_strdup(name));
	add = ft_calloc(1, 1);
	path = env_take(vars, "PATH");
	while (*path)
	{
		if (ft_exists(add))
			return (add);
		ft_bzero(add, ft_strlen(add));
		while (*path && *path != ':')
			add = str_reallocpy(add, *path++);
		add = str_reallocpy(add, '/');
		*path ? path++ : 0;
		add = str_reallocpy_str(add, name);
	}
	free(add);
	g_r_code = 127;
	return (NULL);
}

static void	wait_child(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status) != 0)
		g_r_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			g_r_code = 130;
			write(1, "\n", 1);
		}
		else if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd("^\\Quit (core dumped)\n", 1);
			g_r_code = 131;
		}
	}
	signal(SIGQUIT, handler_sigquit);
	signal(SIGINT, handler_sigint);
}

int			call_extern_prog(t_command *comm, char **envp, t_vars *vars)
{
	t_exe	exe;
	pid_t	pid;
	int		fd[2];
	int		status;

	status = 0;
	pipe(fd);
	get_exe(comm, &exe, vars);
	if (exe.prog && !try_recode_prog(comm->command))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(comm->fd_out, 1);
			execve(exe.prog, exe.ar, envp);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
		}
		else
			wait_child(pid, status);
	}
	else
		try_recode(comm, vars, &exe);
	clean_exe(&exe);
	return (1);
}

int			call_pipe_after_proc(t_command *comm, char **envp, t_vars *vars)
{
	t_exe	exe;
	pid_t	pid;

	get_exe(comm, &exe, vars);
	pipe(vars->fd_pipe);
	vars->command_counter++;
	pid = fork();
	if (pid == 0)
	{
		// if (comm->fd_out == 1)
			// dup2(vars->fd_pipe[1], comm->fd_out);
		dup2(vars->fd_pipe[1], STDOUT_FILENO);
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
		if (!try_recode(comm, vars, &exe))
			execve(exe.prog, exe.ar, envp);
		exit(1);
	}
	else
	{
		// close(vars->fd_pipe[0]);
		// close(vars->fd_pipe[1]);
		waitpid(pid, NULL, 0);
		// dup2(fd[0], comm->fd_in);
		// close(fd[1]);
		// close(fd[0]);
	}
	clean_exe(&exe);
	return (1);
}

int			call_pipe_before_proc(t_command *comm, char **envp, t_vars *vars)
{
	t_exe	exe;
	pid_t	pid;

	get_exe(comm, &exe, vars);
	vars->command_counter++;
	pid = fork();
	if (pid == 0)
	{
		if (vars->command_counter == 3)
		{
			dup2(vars->fd_pipe2[0], STDIN_FILENO);
			close(vars->fd_pipe[0]);
			close(vars->fd_pipe[1]);
			close(vars->fd_pipe2[0]);
			close(vars->fd_pipe2[1]);
		}
		else
		{
			dup2(vars->fd_pipe[0], STDIN_FILENO);
			close(vars->fd_pipe[0]);
			close(vars->fd_pipe[1]);
			close(vars->fd_pipe2[0]);
			close(vars->fd_pipe2[1]);
		}
		if (!try_recode(comm, vars, &exe))
			execve(exe.prog, exe.ar, envp);
		exit(1);
	}
	else
	{
		close(vars->fd_pipe[0]);
		close(vars->fd_pipe[1]);
		close(vars->fd_pipe2[0]);
		close(vars->fd_pipe2[1]);
		waitpid(pid, NULL, 0);
	}
	clean_exe(&exe);
	return (1);
}

int			call_pipe_before_after_proc(t_command *comm, char **envp, t_vars *vars)
{
	t_exe	exe;
	pid_t	pid;

	get_exe(comm, &exe, vars);
	vars->command_counter++;
	if (vars->command_counter == 2)
		if (pipe(vars->fd_pipe2) == -1)
			return (1);
	pid = fork();
	if (pid == 0)
	{

		// if(vars->command_counter % 2 == 0)
		if(vars->command_counter == 2)
		{
			dup2(vars->fd_pipe[0], STDIN_FILENO);
			// dup2(vars->fd[0], vars->fd_pipe[0]);
			dup2(vars->fd_pipe2[1], STDOUT_FILENO);
			// close(vars->fd_pipe[0]);
			close(vars->fd[0]);
			close(vars->fd[1]);
			close(vars->fd_pipe[1]);
			close(vars->fd_pipe2[0]);
			close(vars->fd_pipe2[1]);
		}
		// else if (vars->command_counter % 3 == 0)
		// {
		// 	dup2(vars->fd_pipe2[0], STDIN_FILENO);
		// 	dup2(vars->fd_pipe[1], STDOUT_FILENO);
		// 	close(vars->fd_pipe[0]);
		// 	close(vars->fd_pipe[1]);
		// 	close(vars->fd_pipe2[0]);
		// 	close(vars->fd_pipe2[1]);
		// }
		if (!try_recode(comm, vars, &exe))
			execve(exe.prog, exe.ar, envp);
		exit(1);
	}
	// else
	// {
		// close(vars->fd_pipe[0]);
		// close(vars->fd_pipe[1]);
		waitpid(pid, NULL, 0);
	// }
	clean_exe(&exe);
	return (1);
}
