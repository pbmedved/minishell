/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:01:08 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/18 23:45:40 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			parse_bracks(t_command *comm, t_parse *prs, char c)
{
	if (!set_bracks(prs, c))
		comm->command = str_reallocpy(comm->command, c);
	prs->i++;
}

void			parse_escape(t_command *comm, t_parse *prs, char *buff)
{
	if (prs->brack)
	{
		comm->command = str_reallocpy(comm->command, '\\');
		prs->i++;
	}
	else
	{
		comm->command = str_reallocpy(comm->command, buff[prs->i + 1]);
		prs->i += 2;
	}
}

int				command_write(t_command *comm, char *buff, t_vars *vars)
{
	t_parse		prs;

	prs = (t_parse){0, 0, 0};
	while (buff[prs.i] && check_end(&prs, buff[prs.i]))
	{
		if (buff[prs.i] == '"' || buff[prs.i] == '\'')
			parse_bracks(comm, &prs, buff[prs.i]);
		else if (buff[prs.i] == '\\')
			parse_escape(comm, &prs, buff);
		else if (buff[prs.i] == '$')
			parse_dollar_comm(comm, &prs, buff, vars);
		else
			comm->command = str_reallocpy(comm->command, buff[prs.i++]);
	}
	//TODO проверка if (prs->brack || prs->brack_2) token_error(кобка); end_off_parse();
	return (prs.i);
}

void			parse_bracks_arg(t_args *args, t_parse *prs, char c)
{
	if (!set_bracks(prs, c))
		args->arg = str_reallocpy(args->arg, c);
	prs->i++;
}

void			parse_escape_arg(t_args *args, t_parse *prs, char *buff)
{
	if (brack_status(prs))
	{
		args->arg = str_reallocpy(args->arg, '\\');
		prs->i++;
	}
	else
	{
		args->arg = str_reallocpy(args->arg, buff[prs->i + 1]);
		prs->i += 2;
	}
}
