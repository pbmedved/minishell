/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:02:28 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/16 21:46:32 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env 		*env_create()
{
	t_env 	*env;

	if (!(env = malloc(sizeof(t_env))))
		exit_error("Malloc error", 1);
	env->key = calloc(1,1);
	env->value = calloc(1,1);
	if (!env->key || !env->value)
		exit_error("Calloc error", 1);
	env->next = NULL;
	return (env);
}

void	 		env_add(t_env **main, t_env *new)
{
	t_env		*res;

	if (!*main)
		*main = new;
	else
	{
		res = *main;
		while (res->next)
			res = res->next;
		res->next = new;
	}
}

void		env_save(t_vars *vars, char **envp)
{
	int i;
	int d;

	t_env *env;
	i = 0;
	d = 0;
	while (envp[i])
	{
		env = env_create();
		while(envp[i][d] != '=')
			env->key = str_reallocpy(env->key, envp[i][d++]);
		d++;
		while (envp[i][d])
			env->value = str_reallocpy(env->value, envp[i][d++]);
		env_add(&vars->env, env);
		d = 0;
		i++;
	}
}

char			*env_take(t_vars *vars, const char *key)
{
	char		*value;
	t_env		*env;

	env = vars->env;
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
		{
			value = env->value;
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

void		dell_all_env(t_env **env)
{
	t_env	*main;
	t_env	*res;

	main = *env;
	while (main)
	{
		free(main->key);
		main->key = NULL;
		free(main->value);
		main->value = NULL;
		res = main->next;
		free(main);
		main = res;
	}
	*env = NULL;
}
