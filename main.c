/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/30 07:16:06 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void		preallocated(t_vars *vars)
{
	vars->buff = NULL;
	vars->state = 1;
	vars->comm = NULL;
	vars->env = NULL;
	vars->fd[0] = dup(0);
	vars->fd[1] = dup(1);
	vars->prompt = NULL;
}

int				main(int argc, char **argv, char **envp)
{
	t_vars		vars;

	preallocated(&vars);
	if (argc != 1 && argc != 3)
		exit_error("bad param", -1);
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'c' && !argv[1][2])
		vars.buff = str_reallocpy_str(vars.buff, argv[2]);
	env_save(&vars, envp);
	vars.prompt = ft_strdup(env_take(vars.env, "USER"));
	command_getter(&vars, envp);
	free(vars.prompt);
	free(vars.buff);
	dell_all_env(&vars.env);
	return (0);
}
