/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:18:15 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 16:29:11 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void				command_set_fd_out_end(t_command *comm, char *file)
{
	int fd;

	if ((fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

/*
** Определяет тип редиректа и вызывает соотвествующую функцию.
*/

int					redirect_fd_choose(t_command *comm, t_args *args)
{
	if (!args->next)
	{
		newline_error();
		return (0);
	}
	args->next->state = 2;
	if (!ft_strncmp(args->arg, ">", ft_strlen(args->arg)))
		command_set_fd_out(comm, args->next->arg);
	else if (!ft_strncmp(args->arg, "<", ft_strlen(args->arg)))
		command_set_fd_in(comm, args->next->arg);
	else if (!ft_strncmp(args->arg, ">>", ft_strlen(args->arg)))
		command_set_fd_out_end(comm, args->next->arg);
	return (1);
}

void				redirect_fd_set(t_command *command)
{
	t_args			*args;
	t_command		*comm;

	comm = command;
	while (comm)
	{
		args = comm->args;
		while (args)
		{
			if (args->state == 2)
			{
				if (redirect_fd_choose(comm, args))
					args = args->next;
			}
			args = args->next;
		}
		comm = comm->next;
	}
}

void				command_fix(t_command **comm)
{
	int				i;
	t_command		*res;

	res = *comm;
	command_set_state(res);
	while (res)
	{
		redirect_fd_set(res);
		i = -1;
		while (res->command[++i])
			res->command[i] = (char)ft_tolower(res->command[i]);
		res = res->next;
	}
}

void				input_handler(int res, char b, t_vars *vars)
{
	if (res == 0 && !ft_strlen(vars->buff))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else
	{
		vars->buff = str_reallocpy(vars->buff, b);
		b = '\0';
	}
}
