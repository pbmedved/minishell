/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:18:15 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/27 08:29:29 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		print_prompt(t_vars *vars)
{

	ft_putstr_fd(env_take(vars->env, "USER"), 1);
	write(1, "$ ", 2);
}

void 		command_set_state(t_command *comm)
{
	t_command *res;
	t_args    *args;

	res = comm;
	while (res)
	{
		args = res->args;
		while (args)
		{
			if (args->state == 8)
			{
				res->state = 3;
				break;
			}
			args = args->next;
		}
		res = res->next;
	}
}

void		command_fix(t_command **comm)
{
	int i;
	t_command *res;

	res = *comm;
	command_set_state(res);
	while (res)
	{
		i = -1;
		while (res->command[++i])
			res->command[i] = (char)ft_tolower(res->command[i]);
		res = res->next;
	}
}
void 		command_getter(t_vars *vars, char **envp)
{
	char 	b;

	while(vars->state)
	{
		print_prompt(vars);
		if (!vars->buff)
		{
			if (!(vars->buff = ft_calloc(1,1)))
				exit_error("Malloc error", errno);
			while((read(0,&b, 1)) && b != '\n')
				vars->buff = str_reallocpy(vars->buff, b);
		}
		buff_parser(vars, vars->buff);
		command_fix(&vars->comm);
		command_handler(vars->comm, vars, envp);
		dell_all_command(&vars->comm);
		free(vars->buff);
		vars->buff = NULL;
	}
}