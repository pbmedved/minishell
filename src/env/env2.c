/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:20:53 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/21 12:11:29 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	res = NULL;
	if (node == del)
	{
		res = *env;
		*env = node->next;
	}
	else
	{
		while (node->next != del)
			node = node->next;
		res = node->next;
		if (node->next->next)
			node->next = node->next->next;
	}
	free(res->value);
	free(res->key);
	free(res);
}