/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:01:11 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/09 23:15:53 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void 			print_by_state(char *s, t_args *args)
// {
// 	if (args) {
// //		if (args->state == 1)
// //			ft_printf("%s", s);
// 		if (args->state == 3)
// 			write_in_file(s, args->next);
// 		else if (args->state == 5)
// 			save_write_in_file(s, args->next);
// 	}
// 	else if (s)
// 	{
// 		s = str_reallocpy(s, '\04');
// 		ft_putstr_fd(s, 1);
// 	}

// }

int 		ft_echo(t_command *comm, t_vars **vars) {
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
	while (arg)
	{
		if (arg->state == 1)
		{
			s = str_reallocpy_str(s, arg->arg);
			arg = arg->next;
			if (arg && arg->state <= 2)
				s = str_reallocpy(s, ' ');
		}
		else
			arg = arg->next;
	}
	if (!n)
		s = str_reallocpy(s, '\n');
	if (s)
		write(comm->fd_out, s, ft_strlen(s));
	free(s);
	(*vars)->global_r_code = 0;
	return (1);
}
