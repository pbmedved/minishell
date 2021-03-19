/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:12:03 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/19 23:44:52 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			parse_dollar_comm(t_command *comm, t_parse *prs,
										char *buff, t_vars *vars)
{
	char		*new;
	int			valid;

	valid = 0;
	if (!(new = ft_calloc(1, 1)))
		exit_error("Calloc error", errno);
	if (prs->brack && !prs->brack_2)
		comm->command = str_reallocpy(comm->command, buff[prs->i++]);
	else
	{
		prs->i++;
		if (!ft_isalpha(buff[prs->i]))
		{
			valid = 1;
			prs->i++;
		}
		while (ft_isalnum(buff[prs->i]))
			new = str_reallocpy(new, buff[prs->i++]);
		if (valid)
			comm->command = str_reallocpy_str(comm->command, new);
		else
			comm->command = str_reallocpy_str(comm->command,
										env_take(vars, new));
	}
	free(new);
}

void			parse_dollar_arg(t_args *args, t_parse *prs,
									char *buff, t_vars *vars)
{
	char		*new;
	int			valid;

	valid = 0;
	if (!(new = ft_calloc(1, 1)))
		exit_error("Calloc error", errno);
	if (prs->brack && !prs->brack_2)
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
	else
	{
		prs->i++;
		if (!ft_isalpha(buff[prs->i]) && buff[prs->i] != '?')
		{
			valid = 1;
			prs->i++;
		}
		if (buff[prs->i] == '?' && buff[prs->i - 1] == '$')
		{
			args->arg = str_reallocpy_str(args->arg, env_take(vars, "?"));
			valid = 1;
			prs->i++;
		}
		while (ft_isalnum(buff[prs->i]))
			new = str_reallocpy(new, buff[prs->i++]);
		if (valid)
			args->arg = str_reallocpy_str(args->arg, new);
		else
			args->arg = str_reallocpy_str(args->arg, env_take(vars, new));
	}
	free(new);
}

void			parse_semicolon(t_args *args, t_parse *prs, char *buff)
{
	if (brack_status(prs))
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
	else
	{
		if (buff[prs->i] == ';')
			args->state = 7;
		else
			args->state = 8;
		args->arg = str_reallocpy(args->arg, buff[prs->i++]);
	}
}

int				parse_redirect(t_args *args, t_parse *prs, char *buff)
{
	if (brack_status(prs))
	{
		while (ft_strchr("<>", buff[prs->i]))
			args->arg = str_reallocpy(args->arg, buff[prs->i++]);
		return (0);
	}
	else
	{
		while (ft_strchr("<>", buff[prs->i]) && buff[prs->i])
			args->arg = str_reallocpy(args->arg, buff[prs->i++]);
		args->state = 2;
		return (1);
	}
}

void			buff_parser(t_vars *vars, char *buff, char **envp)
{
	t_command	*new_comm;
	t_args		*new_arg;
	int			i;

	while (*buff)
	{
		buff += whitespace_remove(buff);
		new_comm = command_new();
		i = command_write(new_comm, buff, vars);
		if (i < 0)
		{
			dell_all_command(&new_comm);
			return ;
		}
		buff += i;
		buff += whitespace_remove(buff);
		while (*buff && *buff != ' ')
		{
			if (ft_strchr(";|", *buff))
			{
				new_arg = arg_new();
				buff += pipe_write(new_arg, buff);
				arg_add(&new_comm->args, new_arg);
				buff += whitespace_remove(buff);
				break ;
			}
			new_arg = arg_new();
			i = arg_write(vars, new_arg, buff);
			arg_add(&new_comm->args, new_arg);
			if (i < 0)
			{
				dell_all_command(&new_comm);
				return ;
			}
			buff += i;
			buff += whitespace_remove(buff);
		}
		command_fix(&new_comm);
		command_handler(new_comm, vars, envp);
		dell_all_command(&new_comm);
	}
}
