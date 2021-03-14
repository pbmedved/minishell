/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:48:52 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/14 23:07:09 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

/*
** Проверяет валидность ключа при выполнении команды export.
** 1. Ключ может начинаться либо с буквы либо с _
** 2. В ключе не должно быть скобок - '(' или ')'
*/

static int		check_export(char *key, char *value)
{
	char		*res;

	if (!(ft_isalpha(key[0]) || key[0] == '_'))
	{
		g_r_code = 1;
		return (export_error(key, value));
	}
	else if ((res = ft_strchr(key, '(')))
	{
		g_r_code = 2;
		res++;
		*res = '\0';
		return (token_error(--res));
	}
	else if ((res = ft_strchr(key, ')')))
	{
		g_r_code = 2;
		res++;
		*res = '\0';
		return (token_error(--res));
	}
	else
		return (1);
}

/*
** Реализация стандартной команды export.
** Считывает из команды ключ значение, потом валидирует и добавляет или
** заменяет текущий. Изменяет глобальный код возврата.
*/

int				ft_export_take(t_args *args, char **key, char **value)
{
	char		*command;

	command = args->arg;
	if (command)
	{
		while (*command && *command != '=')
			*key = str_reallocpy(*key, *command++);
		if (*command == '=')
			command++;
		while (*command)
			*value = str_reallocpy(*value, *command++);
		if (check_export(*key, *value) == 0)
			return (0);
	}
	return (1);
}

int				ft_export(t_command *comm, t_vars *vars)
{
	char		*key;
	char		*value;
	t_args		*args;

	args = comm->args;
	key = NULL;
	value = NULL;
	if (!args)
		env_print(vars->env, "declare -x ");
	while (args)
	{
		if (!(ft_export_take(args, &key, &value)))
			return (0);
		if (key && value)
			env_add_or_change(&vars->env, key, value);
		g_r_code = errno;
		return (1);
	}
	return (1);
}//TODO  Не добавляет несколько переменных в одной команде, возможно проблема в ретерне внутри цикла
// TODO не работает добавление переменной без ключа

int				ft_unset(t_command *comm, t_vars *vars)
{
	if (comm->args) //TODO не работает с несколькими аргументами, добавить цикл
		env_del_by_key(&vars->env, comm->args->arg);
	g_r_code = 0;
	return (1);
}

int				env_print(t_env *env, char *prefix)
{
	t_env		*node;

	node = env;
	while (node)
	{
		ft_printf("%s%s=%s\n", prefix, node->key, node->value);
		node = node->next;
	}
	g_r_code = 0;
	return (1);
}
