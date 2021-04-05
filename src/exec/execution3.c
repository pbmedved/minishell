/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:19:30 by iadrien           #+#    #+#             */
/*   Updated: 2021/04/02 23:59:04 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				try_recode_prog(char *name)
{
	if (ft_strcmp("echo", name) || ft_strcmp("cd", name) \
	|| ft_strcmp("pwd", name) || ft_strcmp("export", name) \
	|| ft_strcmp("unset", name) || ft_strcmp("env", name) \
	|| ft_strcmp("exit", name))
		return (1);
	return (0);
}

void			executable(t_command *comm, t_vars *vars, char **envp)
{
	if (comm->state == 3)
		call_extern_prog_pipe(comm, envp, vars);
	else if (comm->state == 4)
		call_pipe_before_proc(comm, envp, vars);
	else
		call_extern_prog(comm, envp, vars);
}

int				try_recode(t_command *comm, t_vars *vars, t_exe *exe)
{
	errno = 0;
	if (!ft_strncmp_revers(comm->command, "echo", 4))
		return (ft_echo(comm));
	else if (!ft_strncmp(comm->command, "cd", 2))
		return (ft_cd(vars, comm));
	else if (!ft_strncmp(comm->command, "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(comm->command, "export", 6))
		return (ft_export(comm, vars));
	else if (!ft_strncmp(comm->command, "unset", 5))
		return (ft_unset(comm, vars));
	else if (!ft_strncmp(comm->command, "env", 3))
		return (env_print(vars->env, ""));
	else if (!ft_strncmp(comm->command, "exit", 4))
		exit_handler(comm, vars, exe);
	return (0);
}

/*
** Обрабатывает команды из списка с командами.
*/

void			command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (!check_pipes(comm) && !check_redirect(comm))
			break ;
		else if (comm->state == 404)
		{
			end_of_file_error();
			break ;
		}
		else
			executable(comm, vars, envp);
		comm = comm->next;
	}
}
