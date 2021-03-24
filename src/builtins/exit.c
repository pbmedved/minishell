/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:19:51 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/24 22:03:37 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** TODO: непонятно надо ли фиксировать g_r_code для exit
*/

void		exit_handler(t_command *comm, t_vars *vars)
{
	int		err_code;

	if (comm->args)
	{
		free(vars->prompt);
		free(vars->buff);
		vars->buff = 0;
		dell_all_env(&vars->env);
		ft_putstr_fd("exit\n", 1);
		err_code = ft_atoi(comm->args->arg);
		dell_all_args(&comm->args);
		exit(err_code);
	}
	exit(0);
}
