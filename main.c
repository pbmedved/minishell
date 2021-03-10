/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 09:24:37 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/10 12:34:31 by iadrien          ###   ########.fr       */
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
	vars->global_r_code = 0;
}

int				g_signal_flag;
char			*g_username;
int				g_r_code;

int				main(int argc, char **argv, char **envp)
{
	t_vars		vars;

	preallocated(&vars);
	g_signal_flag = 0;
	g_r_code = 0;
	if (argc != 1 && argc != 3)
		exit_error("bad param", -1);
	if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'c' && !argv[1][2])
		vars.buff = str_reallocpy_str(vars.buff, argv[2]);
	env_save(&vars, envp);
	vars.prompt = ft_strdup(env_take(&vars, "USER"));
	g_username = vars.prompt;
	command_getter(&vars, envp);
	free(vars.prompt);
	free(vars.buff);
	vars.buff = 0;
	dell_all_env(&vars.env);
	return (0);
}
