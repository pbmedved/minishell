/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:19:51 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/08 23:31:46 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: непонятно надо ли фиксировать global_r_code для exit
void 			exit_handler(t_command *comm)
{
	if (comm->args)
		exit(ft_atoi(comm->args->arg));
	exit(0);
}