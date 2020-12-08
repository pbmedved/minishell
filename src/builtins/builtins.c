/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:48:52 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/08 23:06:01 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

/*
** Проверяет валидность ключа при выполнении команды export.
** 1. Ключ может начинаться либо с буквы либо с _
** 2. В ключе не должно быть скобок - '(' или ')'
*/
static int	check_export(char *key, char *value, t_vars **vars)
{
	char	*res;

	if (!(ft_isalpha(key[0]) || key[0] == '_'))
	{
		(*vars)->global_r_code = 1;
		return (export_error(key, value));
	}
	else if ((res = ft_strchr(key, '(')) || (res = ft_strchr(key, ')')))
	{
		(*vars)->global_r_code = 2;
		res++;
		*res = '\0'; // TODO: сделал так чтобы не менять твою token_error. Может эту строку надо переделать.т.к. изврат
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
int 		ft_export(t_command *comm, t_vars **vars)
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
		if (check_export(key, value, vars) == 0)
				return (0);
		if (key && value)
			env_add_or_change(&(*vars)->env, key, value);
		(*vars)->global_r_code = errno;
		return (1);
	}
	return (0);
}

int 		ft_unset(t_command *comm, t_vars **vars)
{
	if (comm->args)
		env_del_by_key(&(*vars)->env, comm->args->arg);
	(*vars)->global_r_code = 0;
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

int 		ft_cd(t_vars **vars, t_command *comm)
{
	char s[PATH_MAX];
	int		dir;

	if (!comm->args || comm->args->state == 7)
		dir = chdir(env_take((*vars)->env, "HOME"));
	else
		dir = chdir(comm->args->arg);
	if (dir == -1)
	{
		(*vars)->global_r_code = errno;
		return (print_file_error(comm->args->arg));
	}
	env_add_or_change(&(*vars)->env, "OLDPWD", env_take((*vars)->env, "PWD"));
	getcwd(s, PATH_MAX); //TODO: возможно надо добавить обработку ошибки?
	(*vars)->global_r_code = errno;
	env_add_or_change(&(*vars)->env, "PWD", s);
	return (1);
}

/*
** Возвращает полный путь к директории из которой запущена.
** global_r_code устанавливает = 0 потому что штатная даже
** в удаленной папке не изменяет значение переменной ? в обычном bash
*/
int 		ft_pwd(t_vars **vars, t_command *command)
{
	char		pwd[PATH_MAX];
	t_command	*tmp_c;

	tmp_c = command; // TODO: убрать заглушку или параметр функции. не используется пока
	tmp_c++;
	if (!getcwd(pwd, PATH_MAX))
	{
		;
		// exit_error("GETCWD ERROR", errno); // TODO: думаю надо убрать, т.к. это не совпадает с поведением стандартной функции pwd
	}
	(*vars)->global_r_code = 0;
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
}
