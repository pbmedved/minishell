/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:19:51 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/12 23:43:48 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** TODO: непонятно надо ли фиксировать g_r_code для exit
*/

void		exit_handler(t_command *comm)
{
	if (comm->args)
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(comm->args->arg));
	}
	exit(0);
}
