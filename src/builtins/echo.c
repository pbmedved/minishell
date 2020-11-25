/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:01:11 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/25 09:59:08 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void 			print_by_state(char *s, t_args *args)
{
	if (args) {
		if (args->state == 1)
			ft_printf("%s", s);
		else if (args->state == 3)
			write_in_file(s, args->next);
		else if (args->state == 5)
			save_write_in_file(s, args->next);
	}
	else if (s)
		ft_putstr_fd(s, 1);
}

int 		ft_echo(t_command *comm) {
	t_args *arg;
	char *s;
	int n;

	s = NULL;
	n = 0;

	arg = comm->args;
	while (arg && !ft_strncmp(arg->arg, "-n", ft_strlen(arg->arg)))
	{
		n++;
		arg = arg->next;
	}
	while (arg && arg->state == 1)
	{
		s = str_reallocpy_str(s, arg->arg);
		arg = arg->next;
		if (arg && arg->state == 1)
			s = str_reallocpy(s, ' ');
		else if (!n)
			s = str_reallocpy(s, '\n');
	}
//	print_by_state(s, arg);
	write(1, s, ft_strlen(s));
	return (1);
}
