/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:43:18 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/18 21:28:56 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command			*command_new(void)
{
	t_command		*new_comm;

	if (!(new_comm = malloc(sizeof(t_command))))
		exit_error("Malloc error", 1);
	if (!(new_comm->command = ft_calloc(1, 1)))
		exit_error("Malloc error", 1);
	new_comm->next = NULL;
	new_comm->args = NULL;
	new_comm->fd_in = 0;
	new_comm->fd_out = 1;
	new_comm->state = 1;
	return (new_comm);
}

void				dell_all_command(t_command **command)
{
	t_command		*main;
	t_command		*res;

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

void				command_set_state(t_command *comm)
{
	t_command		*res;
	t_args			*args;

	res = comm;
	while (res)
	{
		args = res->args;
		while (args)
		{
			if (args->state == 8)
			{
				res->state = 3;
				break ;
			}
			args = args->next;
		}
		res = res->next;
	}
}

void				command_set_fd_out(t_command *comm, char *file)
{
	int				fd;

	if ((fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

static int			check_redirect_args(t_command *comm)
{
	t_args			*args;

	args = comm->args;
	while (ft_strchr(args->arg, '<') || ft_strchr(args->arg, '>'))
		args = args->next;
	if(ft_isalpha(*(args->arg)))
			return (1);
	return (0);
}

void				command_set_fd_in(t_command *comm, char *file)
{
	int				fd;

	if (!check_redirect_args(comm))
	{
		newline_error();
		return ;
	}
	if ((fd = open(file, O_RDWR, 0644)) < 0)
	{
		// permission_error(comm->command, file);
		file_not_found(comm->command, file);
		return ;
	}
	comm->fd_in = fd;
}
