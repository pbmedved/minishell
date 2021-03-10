/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:50:19 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 11:08:00 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			token_error(char *err)
{
	ft_putstr_fd("-bash: syntax error near unexpected token '", 2);
	write(2, err, ft_strlen(err));
	write(2, "'\n", 2);
	return (0);
}

void 		which_token_err(char *buf)
{
	if (buf[0] == ';' && buf[1] == ';')
		token_error(";;");
	else if (buf[0] == ';' && buf[1] != ';')
		token_error(";");
	else if (buf[0] == '|' && buf[1] == '|')
		token_error("||");
	else
		token_error("|");
}

void 	exit_error(char *s, int n)
{
	write(2,"Error\n",6);
	write(2,s,ft_strlen(s));
	exit(n);
}

void 		print_command_error(t_command *comm)
{
	write(2, "bash: -bash: ",13);
	write(2, comm->command, ft_strlen(comm->command));
	write(2, ": command not found\n",20);
}


int		print_file_error(char *s)
{
	write(2, "bash: -cd: ",11);
	write(2, s, ft_strlen(s));
	write(2, ": No such file or directory\n",28);
	return (1);
}

int		export_error(char *key, char *value)
{
	ft_printf("minishell: export: `%s=%s': not a valid identifier\n", key, value);
	return (0);
}