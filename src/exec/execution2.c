/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:13:44 by iadrien           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		set_exe_arg(t_exe **ext_exe, t_command *comm)
{
	t_exe		*exe;
	t_args		*arg;
	int			i;

	i = 0;
	arg = comm->args;
	exe = *ext_exe;
	exe->ar[i] = exe->prog;
	i++;
	while (arg && arg->state != 7 && arg->state != 8)
	{
		if (arg->state == 1)
		{
			exe->ar[i] = ft_strdup(arg->arg);
			i++;
		}
		arg = arg->next;
	}
	exe->ar[i] = NULL;
}

static int		print_err_for_check_redirect(char *buf)
{
	which_token_err(buf);
	free(buf);
	return (0);
}

int				check_redirect(t_command *command)
{
	t_command	*comm;
	t_args		*args;
	char		*buf;

	comm = command;
	buf = NULL;
	while (comm)
	{
		args = comm->args;
		while (args)
		{
			if (args->state == 7 || args->state == 8)
			{
				if (ft_strlen(args->arg) == 1 && !comm->command[0])
					buf = str_reallocpy(buf, args->arg[0]);
				else if (ft_strlen(args->arg) > 1)
					buf = str_reallocpy_str(buf, args->arg);
			}
			args = args->next;
		}
		comm = comm->next;
	}
	if (!buf)
		return (1);
	return (print_err_for_check_redirect(buf));
}

void			get_exe(t_command *comm, t_exe *exe, t_vars *vars)
{
	if (try_recode_prog(comm->command))
		exe->prog = ft_strdup(comm->command);
	else
		exe->prog = try_find_prog(comm->command, vars);
	if (!exe->prog && ft_strchr("./", comm->command[0]))
	{
		print_file_error(comm->command);
		return ;
	}
	else if (!exe->prog)
	{
		print_command_error(comm);
		return ;
	}
	if (!(exe->ar = malloc((arg_count(comm) + 2) * sizeof(char *))))
		exit_error("Malloc error", 1);
	set_exe_arg(&exe, comm);
	comm->state = 1;
}

void			clean_exe(t_exe *exe)
{
	int			i;

	i = 0;
	if (exe->prog)
	{
		while (exe->ar[i])
			free(exe->ar[i++]);
		free(exe->ar);
	}
}
