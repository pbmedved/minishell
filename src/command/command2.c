/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:18:15 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/02 08:34:01 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		print_prompt(t_vars *vars)
{

	ft_putstr_fd(vars->prompt, 1);
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
void 			permission_error(char *prog, char *file)
{
	write(2, prog, ft_strlen(prog));
	write(2, ":", 1);
	write(2, file, ft_strlen(file));
	write(2, ": Permission denied\n", 21);
}

void 			command_set_fd_out(t_command *comm, char redir, char *file)
{
	int fd;

	if ((fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

void 			command_set_fd_in(t_command *comm, char redir, char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_in = fd;
}

void 			command_set_fd_out_end(t_command *comm, char *file)
{
	int fd;

	if ((fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
	{
		permission_error(comm->command, file);
		return ;
	}
	comm->fd_out = fd;
}

void 			newline_error()
{
	write(2,"-bash: syntax error near unexpected token `newline'\n", 53);
}

int			redirect_fd_choose(t_command *comm, t_args *args)
{
	if (!args->next)
	{
		newline_error();
		return (0);
	}
	args->next->state = 2;
	if(!ft_strncmp(args->arg, ">", ft_strlen(args->arg)))
		command_set_fd_out(comm, '>', args->next->arg);
	else if(!ft_strncmp(args->arg, "<", ft_strlen(args->arg)))
		command_set_fd_in(comm, '<', args->next->arg);
	else if(!ft_strncmp(args->arg, ">>", ft_strlen(args->arg)))
		command_set_fd_out_end(comm, args->next->arg);
	return (1);
}

void	 		redirect_fd_set(t_command *command)
{
	t_args		*args;
	t_command   *comm;

	comm = command;
	while (comm)
	{
		args = comm -> args;
		while (args) {
			if (args->state == 2)
			{
				if (redirect_fd_choose(comm,args))
					args = args -> next;
			}
			args = args -> next;
		}
		comm = comm -> next;
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
		redirect_fd_set(res);
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
			while((read(vars->fd[0], &b, 1)) && b != '\n')
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