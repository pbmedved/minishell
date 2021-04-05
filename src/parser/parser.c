/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:12:03 by iadrien           #+#    #+#             */
/*   Updated: 2021/04/05 23:23:58 by amayor           ###   ########.fr       */
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

/*
** Проверяет есть ли ранее считанная команда при нахождении пайпа
*/
static int		check_comm_before_pipe(t_command *comm)
{
	if (ft_strlen(comm->command) > 0)
		return (1);
	return (0);
}

int				check_exist_comm()
{
	return 0;
}



void			check_set_command_status(t_command *comm)
{
	if (comm->state == PIPE_BEFORE_FLAG)
		comm->state = PIPE_AFT_BF_FLAG;
	else if (comm->state == NO_PIPE)
		comm->state = PIPE_AFTER_FLAG;
}

/*
** Обработка встреченного пайпа.
** В зависимости от того как расположен пайп или пайпы относительно команды
** выставляем статусы.
*/
char			*pipe_processing(t_command *new_comm, t_args *new_arg,
										 char *buff, t_vars *vars)
{
	if (check_comm_before_pipe(new_comm))
	{
		check_set_command_status(new_comm);
		pipe_write(new_arg, buff, PIPE_BEFORE_FLAG);
	}
	else if (!check_comm_before_pipe(new_comm))
	{
		buff += pipe_write(new_arg, buff, PIPE_AFTER_FLAG);
		buff += buff_parser_command(buff, new_comm, vars);
		new_comm->state = PIPE_BEFORE_FLAG;
	}
	return (buff);
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
			if (ft_strchr(";|", *buff) && take_last_args_arg(new_comm->args))
				buff++;
			else if (ft_strchr(";|", *buff))
			{
				buff = pipe_processing(new_comm, new_arg, buff, vars);
				if (new_comm->state == PIPE_AFTER_FLAG || new_comm->state == PIPE_AFT_BF_FLAG)
				{
					arg_add(&new_comm->args, new_arg);
					break ;
				}
			}
			buff += buff_parser_args(buff, new_arg, vars);
			arg_add(&new_comm->args, new_arg);
		}
		command_fix(&new_comm);
		command_handler(new_comm, vars, envp);
		dell_all_command(&new_comm);
	}
}

// void			buff_parser(t_vars *vars, char *buff, char **envp)
// {
// 	t_command	*new_comm;
// 	t_args		*new_arg;

// 	while (*buff)
// 	{
// 		new_comm = command_new();
// 		buff += buff_parser_command(buff, new_comm, vars);
// 		while (*buff && *buff != ' ')
// 		{
// 			new_arg = arg_new();
// 			if (ft_strchr(";|", *buff) && take_last_args_arg(new_comm->args))
// 				buff++;
// 			else if (ft_strchr(";|", *buff))
// 			{
// 				if (check_comm_before_pipe(new_comm))
// 					pipe_write(new_arg, buff, PIPE_BEFORE_FLAG);
// 				else if (!check_comm_before_pipe(new_comm))
// 				{
// 					buff += pipe_write(new_arg, buff, PIPE_AFTER_FLAG);
// 					buff += buff_parser_command(buff, new_comm, vars);
// 				}
// 				arg_add(&new_comm->args, new_arg);
// 				break ;
// 			}
// 			buff += buff_parser_args(buff, new_arg, vars);
// 			arg_add(&new_comm->args, new_arg);
// 		}
// 		command_fix(&new_comm);
// 		command_handler(new_comm, vars, envp);
// 		dell_all_command(&new_comm);
// 	}
// }
