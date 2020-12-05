/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:13:44 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/03 14:34:58 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 		check_redirect(t_command *command)
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

/*
** Обрабатывает команды из списка с командами.
** 
**
*/
void 		command_handler(t_command *comm, t_vars *vars, char **envp)
{
	while (comm)
	{
		if (!check_pipes(comm) && !check_redirect(comm))
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
	exe->ar[i] = exe->prog;
	i++;
	while (arg && arg->state != 7 && arg->state != 8)
	{
		if (arg->state == 1)
		{
			exe->ar[i] = ft_strdup(arg->arg);
			i++;
		}
		arg = arg->next;

	}
	exe->ar[i] = NULL;
	comm->state = 1;
}

void	clean_exe(t_exe *exe)
{
	int i;

	i = 0;
	while (exe->ar[i])
		free(exe->ar[i++]);

	free(exe->ar);
}