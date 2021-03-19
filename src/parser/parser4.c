/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:35:42 by amayor            #+#    #+#             */
/*   Updated: 2021/03/19 23:40:14 by iadrien          ###   ########.fr       */
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
		else if (ft_strchr("<>", buff[prs.i]) && !brack_status(&prs))
		{
			if (parse_redirect(args, &prs, buff))
				return (prs.i);
		}
		else
			args->arg = str_reallocpy(args->arg, buff[prs.i++]);
		if (ft_strchr("<>", buff[prs.i]) && !brack_status(&prs))
			return (prs.i);
	}
	if (brack_status(&prs))
	{
		end_of_file_error();
		prs.i = -404;
	}
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
