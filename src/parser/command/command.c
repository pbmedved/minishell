/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:43:18 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/16 15:26:56 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_command		*command_new()
{
	t_command 	*new_comm;

	if (!(new_comm = malloc(sizeof(t_command))))
		exit_error("Malloc error", 1);
	new_comm->next = NULL;
	new_comm->args = NULL;
	new_comm->state = 1;
	if (!(new_comm->command = ft_calloc(1,1)))
		exit_error("Calloc error", 1);
	return (new_comm);
}

void 			command_add(t_command **comm, t_command *new)
{
	t_command	*res;

	if (!*comm)
		*comm = new;
	else
	{
		res = *comm;
		while (res->next)
			res = res->next;
		res->next = new;
	}
}

void			dell_all_command(t_command **command)
{
	t_command	*main;
	t_command	*res;

	main = *command;
	while (main)
	{
		dell_all_args(&main->args);
		res = main->next;
		free(main->command);
		main->command = NULL;
		free(main);
		main = res;
	}
	*command = NULL;
}
