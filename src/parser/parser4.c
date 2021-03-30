/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:35:42 by amayor            #+#    #+#             */
/*   Updated: 2021/03/30 23:02:18 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				arg_write(t_vars *vars, t_args *args, char *buff)
{
	t_parse		prs;

	prs = (t_parse){0, 0, 0};
	while (buff[prs.i] && check_end(&prs, buff[prs.i]))
	{
		if (buff[prs.i] == '"' || buff[prs.i] == '\'')
			parse_bracks_arg(args, &prs, buff[prs.i]);
		else if (buff[prs.i] == '\\')
			parse_escape_arg(args, &prs, buff);
		else if (buff[prs.i] == '$' && buff[prs.i + 1] != '"')
			parse_dollar_arg(args, &prs, buff, vars);
		else if (buff[prs.i] == ';' || buff[prs.i] == '|')
			parse_semicolon(args, &prs, buff);
		else if (ft_strchr("<>", buff[prs.i]) && !brack_status(&prs) \
		&& parse_redirect(args, &prs, buff))
			return (prs.i);
		else
			args->arg = str_reallocpy(args->arg, buff[prs.i++]);
		if (ft_strchr("<>", buff[prs.i]) && !brack_status(&prs))
			return (prs.i);
	}
	if (brack_status(&prs))
		args->state = 404;
	return (prs.i);
}

int				pipe_write(t_args *args, char *buff)
{
	while (*buff && ft_strchr(";|<>", *buff))
	{
		args->arg = str_reallocpy(args->arg, *buff);
		if (*buff == ';')
			args->state = 7;
		else if (*buff == '|')
			args->state = 8;
		else if (*buff == '>' && buff[1] != '>')
			args->state = 3;
		else if (*buff == '<')
			args->state = 4;
		else if (*buff == '>' && buff[1] == '>')
		{
			args->state = 5;
			return (2);
		}
		else if (*buff == '<' && buff[1] == '<')
		{
			args->state = 4;
			return (2);
		}
		buff++;
	}
	return (ft_strlen(args->arg));
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

int				buff_parser_command(char *buff, t_command *new_comm,\
t_vars *vars)
{
	int			i;
	int			d;

	i = 0;
	d = whitespace_remove(buff);
	buff += d;
	i += d;
	d = command_write(new_comm, buff, vars);
	buff += d;
	i += d;
	d = whitespace_remove(buff);
	i += d;
	return (i);
}

int				buff_parser_args(char *buff, t_args *args, t_vars *vars)
{
	int			i;
	int			d;

	i = 0;
	d = whitespace_remove(buff);
	buff += d;
	i += d;
	d = arg_write(vars, args, buff);
	buff += d;
	i += d;
	d = whitespace_remove(buff);
	i += d;
	return (i);
}
