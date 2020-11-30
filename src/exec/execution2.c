/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:13:44 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/27 14:22:15 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 		command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (!check_args(comm))
			break;
		else
			executable(comm, vars, envp);
		comm = comm->next;
	}
}

void 	get_exe(t_command *comm, t_exe *exe, t_vars *vars)
{
	t_args *arg;
	int i;

	i = 0;
	arg = comm->args;
	if (!(exe->ar = malloc((arg_count(comm) + 2) * sizeof(char *))))
		exit_error("Malloc error", 1);
	if (try_recode_prog(comm->command))
		exe->prog = ft_strdup(comm->command);
	else
		exe->prog = try_find_prog(comm->command, vars);
	if (!exe->prog)
		print_command_error(comm);
	exe->ar[i++] = exe->prog;
	while (arg && arg->state == 1)
	{
		exe->ar[i++] = arg->arg;
		arg = arg->next;
	}
	exe->ar[i] = NULL;
	comm->state = 1;
}

void	clean_exe(t_exe *exe)
{
	int i;

	i = 0;
	exe->prog = NULL;
	exe->ar = NULL;
}