/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:19:30 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 18:20:28 by iadrien          ###   ########.fr       */
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
	else
		call_extern_prog(comm, envp, vars);
}

int			try_recode(t_command *comm, t_vars *vars)
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
		exit_handler(comm);
	return (0);
}