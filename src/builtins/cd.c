/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:41:28 by iadrien           #+#    #+#             */
/*   Updated: 2021/04/07 23:53:53 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

char			*path_fix(t_vars *vars, char *path)
{
	char *newPath;

	newPath = NULL;
	if(path && *path == '~')
	{
		newPath = ft_strdup(env_take(vars, "HOME"));
		path++;
	}
	newPath = str_reallocpy_str(newPath, path);
	return (newPath);
}

int				ft_cd(t_vars *vars, t_command *comm)
{
	char		s[PATH_MAX];
	int			dir;
	char		*path;

	path = NULL;
	if (!comm->args || comm->args->state == 7)
		dir = chdir(env_take(vars, "HOME"));
	else
	{
		path = path_fix(vars, comm->args->arg);
		dir = chdir(path);
	}
	if (dir == -1)
	{
		g_r_code = 1;
		if (!comm->args)
			return (no_home_error());
		return (print_file_error(path));
	}
	env_add_or_change(&vars->env, "OLDPWD", env_take(vars, "PWD"));
	if (!(getcwd(s, PATH_MAX)))
	{
		write(2, "getcwd error\n", 13);
		return (0);
	}
	g_r_code = errno;
	env_add_or_change(&vars->env, "PWD", s);
	free(path);
	return (1);
}

/*
** Возвращает полный путь к директории из которой запущена.
** g_r_code устанавливает = 0 потому что штатная даже
** в удаленной папке не изменяет значение переменной ? в обычном bash
*/

int				ft_pwd(void)
{
	char		pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		write(2, "getcwd error\n", 13);
		return (0);
	}
	g_r_code = 0;
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (1);
}
