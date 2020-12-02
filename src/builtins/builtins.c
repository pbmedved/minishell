/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:48:52 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/01 23:49:55 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 		ft_export(t_command *comm, t_vars *vars)
{
	if (comm->args && comm->args->next)
		env_add_or_change(&vars->env, comm->args->arg, comm->args->next->arg);
	return (1);
}

int 		ft_unset(t_command *comm, t_vars *vars)
{
	if (comm->args)
		env_del_by_key(&vars->env, comm->args->arg);
	return (1);
}

int 		env_print(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env=env->next;
	}
	return (1);
}

int 		ft_cd(t_vars *vars, t_command *comm)
{
	char s[PATH_MAX];
	int		dir;

	if (!comm->args || comm->args->state == 7)
		dir = chdir(env_take(vars->env, "HOME"));
	else
		dir = chdir(comm->args->arg);
	if (dir == -1)
		exit_error("dir error", errno);
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars->env, "PWD"));
	getwd(s); // TODO: getwd - deprecated надо использовать getcwd()
	env_add_or_change(&vars->env, "PWD", s);
	return (1);
}

int 		ft_pwd(t_vars *vars, t_command *command)
{
	char *pwd;

	pwd = NULL;
	pwd = env_take(vars->env, "PWD");
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
}