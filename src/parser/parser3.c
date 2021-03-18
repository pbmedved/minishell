/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:03:45 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/18 23:47:59 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_token_symb(char c)
{
	if (c == ';' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int				check_pipes(t_command *command)
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
	which_token_err(buf);
	free(buf);
	return (0);
}

int				check_end(t_parse *parse, char c)
{
	if (ft_strchr(" |;", c))
	{
		if (parse->brack || parse->brack_2)
			return (1);
		else
			return (0);
	}
	return (1);
}

int				set_bracks(t_parse *prs, char c)
{
	if (c == '"')
	{
		prs->brack_2 = prs->brack_2 ? 0 : 1;
		if (prs->brack)
			return (0);
		return (1);
	}
	else if (c == '\'')
	{
		prs->brack = prs->brack ? 0 : 1;
		if (prs->brack_2)
			return (0);
		return (1);
	}
	return (1);
}

int				brack_status(t_parse *prs)
{
	if (prs->brack_2 || prs->brack)
		return (1);
	return (0);
}
