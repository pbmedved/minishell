/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amayor <amayor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:20:53 by iadrien           #+#    #+#             */
/*   Updated: 2020/12/07 20:41:49 by amayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char			*take_env_by_arg(t_vars *vars, char *s)
{
	char *key;
	char *new_s;
	char *value;
	int 	i;

	i = 0;
	new_s = NULL;
	key = NULL;

	while(s[i])
	{
		if (s[i] == '$')
		{
			i++;
			while (s[i] && s[i] != ' ')
				key = str_reallocpy(key, s[i++]);
			value = env_take(vars->env, key);
			new_s = str_reallocpy_str(new_s, value);
			key = NULL;
		}
		else
			new_s = str_reallocpy(new_s, s[i++]);
	}
	return (new_s);

}

t_env			*env_take_ptr(t_env *env, const char *key)
{
	t_env		*res;

	res = env;
	while (res)
	{
		if (!ft_strncmp(key, res->key, ft_strlen(res->key)))
			return (res);
		res = res->next;
	}
	return (NULL);
}

void			env_del_by_key(t_env **env, char *key)
{
	t_env *node;
	t_env *res;
	t_env *del;

	del = env_take_ptr(*env, key);
	if (!del)
		return ;
	node = *env;
	if (node == del)
		*env = node->next;
	else
	{
		while (node->next != del)
			node = node->next;
		del = node->next;
		res = node->next->next;
		node->next = res;
	}
	free(del->value);
	free(del->key);
	free(del);
	del = NULL;
}

void 		env_add_or_change(t_env **env, char *key, char *value)
{
	t_env *res;
	t_env *new;

	res = env_take_ptr(*env, key);
	if (!res)
	{
		new = env_create();
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		env_add(env, new);
	}
	else
	{
		free(res->value);
		res->value = ft_strdup(value);
	}
}

void			env_del_one(t_env *del)
{
	if (del)
	{
		free(del->key);
		free(del->value);
		free(del);
		del = NULL;
	}
}