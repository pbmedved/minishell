/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:48:52 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/02 21:30:08 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 		ft_export(t_command *comm, t_vars *vars)
{
	char	*key;
	char	*value;
	char	*command;

	key = NULL;
	value = NULL;
	command = NULL;
	if (comm->args)
		command = comm->args->arg;
	if (command)
	{
		while (*command && *command != '=')
			key = str_reallocpy(key, *command++);
		if (*command == '=')
			command++;
		while (*command)
			value = str_reallocpy(value, *command++);
		if (key && value)
			env_add_or_change(&vars->env, key, value);
		return (1);
	}
	return (0);
}

int 		ft_unset(t_command *comm, t_vars *vars)
{
	if (comm->args)
		env_del_by_key(&vars->env, comm->args->arg);
	return (1);
}

int 		env_print(t_env *env)
{
	t_env  *node;

	node = env;
	while (node)
	{
		ft_printf("%s=%s\n", node->key, node->value);
		node = node->next;
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
		return (print_file_error(comm->args->arg));
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars->env, "PWD"));
	getwd(s); // TODO: getwd - deprecated надо использовать getcwd()
	env_add_or_change(&vars->env, "PWD", s);
	return (1);
}

int 		ft_pwd(t_vars *vars, t_command *command)
{
	char pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		exit_error("GETCWD ERROR", errno);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
}