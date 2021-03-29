/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:01:11 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/29 10:49:28 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		ft_echo_n_flag(t_args **arg, int *n)
{
	while (*arg && (*arg)->arg[0] == '-' && (*arg)->arg[1] == 'n')
	{
		*n = 1;
		*arg = (*arg)->next;
		if (*arg && (*arg)->arg[0] != '-' && (*arg)->arg[1] != 'n')
			return ;
	}
}

int				ft_echo(t_command *comm)
{
	t_args		*arg;
	char		*s;
	int			n;

	s = NULL;
	n = 0;
	arg = comm->args;
	ft_echo_n_flag(&arg, &n);
	while (arg && arg->state == 1)
	{
		s = str_reallocpy_str(s, arg->arg);
		arg = arg->next;
		if (arg && arg->state <= 2 && !ft_strcmp(s, ""))
			s = str_reallocpy(s, ' ');
	}
	if (!n)
		s = str_reallocpy(s, '\n');
	if (s)
		write(comm->fd_out, s, ft_strlen(s));
	free(s);
	g_r_code = 0;
	return (1);
}
