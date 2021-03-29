/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:19:51 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/29 09:26:09 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** TODO: непонятно надо ли фиксировать g_r_code для exit
*/

void		exit_handler(t_command *comm, t_vars *vars, t_exe *exe)
{
	int		err_code;
	err_code = 0;
	if (arg_count(comm) > 1)
		return (to_many_args_error());
	if (comm->args)
		err_code = ft_atoi(comm->args->arg);
	free(vars->prompt);
	free(vars->buff);
	vars->buff = 0;
	dell_all_env(&vars->env);
	ft_putstr_fd("exit\n", 1);
	dell_all_args(&comm->args);
	free(comm->command);
	free(comm);
	clean_exe(exe);
	exit(err_code);
}
