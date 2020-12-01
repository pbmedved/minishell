/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:48:00 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/21 14:44:07 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_args			*arg_new()
{
	t_args 		*new_arg;

	if (!(new_arg = malloc(sizeof(t_args))))
		exit_error("Malloc error", 1);
	if (!(new_arg->arg = ft_calloc(1,1)))
		exit_error("Malloc error", 1);
	new_arg->next = NULL;
	new_arg->state = 1;
	return (new_arg);
}

void 			arg_add(t_args **arg, t_args *new)
{
	t_args		*res;
	if (!*arg)
		*arg = new;
	else
	{
		res = *arg;
		while (res->next)
			res = res->next;
		res->next = new;
	}
}

void		dell_all_args(t_args **arg)
{
	t_args	*main;
	t_args	*res;
	main = *arg;
	while (main)
	{
		res = main->next;
		free(main->arg);
		main->arg = NULL;
		free(main);
		main = res;
	}
	*arg = NULL;
}

int 			arg_count(t_command *comm)
{
	t_command *res;
	int i;

	i = 0;
	res = comm;
	while (res)
	{
		if (res->state == 1)
			i++;
		res = res->next;
	}
	return (i);
}