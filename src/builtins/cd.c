/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:41:28 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 15:41:36 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

int				ft_cd(t_vars *vars, t_command *comm)
{
	char		s[PATH_MAX];
	int			dir;

	if (!comm->args || comm->args->state == 7)
		dir = chdir(env_take(vars, "HOME"));
	else
		dir = chdir(comm->args->arg);
	if (dir == -1)
	{
		g_r_code = 1;
		return (print_file_error(comm->args->arg));
	}
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars, "PWD"));
	if (!(getcwd(s, PATH_MAX)))
	{
		write(2, "getcwd error\n", 13);
		return (0);
	}
	g_r_code = errno;
	env_add_or_change(&vars->env, "PWD", s);
	return (1);
}
