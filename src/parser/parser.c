/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:12:03 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/22 21:21:22 by iadrien          ###   ########.fr       */
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

int				parse_dollar_arg_valid(t_vars *vars, t_args *args, \
t_parse *prs, char *buff)
{
	if (!ft_isalpha(buff[prs->i]) && buff[prs->i] != '?')
	{
		return (1);
	}
	if (buff[prs->i] == '?' && buff[prs->i - 1] == '$')
	{
		args->arg = str_reallocpy_str(args->arg, env_take(vars, "?"));
		return (1);
	}
	return (0);
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
		if (parse_dollar_arg_valid(vars, args, prs, buff))
		{
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

void			buff_parser(t_vars *vars, char *buff, char **envp)
{
	t_command	*new_comm;
	t_args		*new_arg;

	while (*buff)
	{
		new_comm = command_new();
		buff += buff_parser_command(buff, new_comm, vars);
		while (*buff && *buff != ' ')
		{
			new_arg = arg_new();
			if (ft_strchr(";|", *buff))
			{
				buff += pipe_write(new_arg, buff);
				arg_add(&new_comm->args, new_arg);
				break ;
			}
			buff += arg_write(vars, new_arg, buff);
			buff += whitespace_remove(buff);
			arg_add(&new_comm->args, new_arg);
		}
		command_fix(&new_comm);
		command_handler(new_comm, vars, envp);
		dell_all_command(&new_comm);
	}
}
