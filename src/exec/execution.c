/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:07:35 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/11 21:20:41 by amayor           ###   ########.fr       */
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
		if (ft_exists(name))
			return (add);
		ft_bzero(add, ft_strlen(add));
		while (*path && *path != ':')
			add = str_reallocpy(add, *path++);
		add = str_reallocpy(add, '/');
		path++;
		add = str_reallocpy_str(add, name);
	}
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
			g_r_code = 130;
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
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			execve(exe.prog, exe.ar, envp);
		}
		else
			wait_child(pid, status);
	}
	else
		try_recode(comm, vars);
	clean_exe(&exe);
	return (1);
}

int			call_extern_prog_pipe(t_command *comm, char **envp, t_vars *vars)
{
	t_exe	exe;
	pid_t	pid;
	int		fd[2];

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
		dup2(fd[0], comm->fd_in);
		close(fd[1]);
		close(fd[0]);
	}
	clean_exe(&exe);
	return (1);
}
