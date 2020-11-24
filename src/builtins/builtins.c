/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:48:52 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/22 10:50:18 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void 		ft_export(t_command *comm, t_vars *vars)
{
	if (comm->args && comm->args->next)
		env_add_or_change(&vars->env, comm->args->arg, comm->args->next->arg);
}

void 		ft_unset(t_command *comm, t_vars *vars)
{
	if (comm->args)
		env_del_by_key(&vars->env, comm->args->arg);
}

void 		env_print(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env=env->next;
	}
}

void 		ft_cd(t_vars *vars, t_command *comm)
{
	char s[PATH_MAX];
	int		dir;
	if (!comm->args)
		dir = chdir(env_take(vars->env, "HOME"));
	else
		dir = chdir(comm->args->arg);
	if (dir == -1)
		exit_error("dir error", errno);
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars->env, "PWD"));
	getwd(s);
	env_add_or_change(&vars->env, "PWD", s);
}

void 		ft_pwd(t_vars *vars, t_command *command)
{
	char *pwd;

	pwd = env_take(vars->env, "PWD");

	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}