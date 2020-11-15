/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:45:26 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/15 22:49:57 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_reallocpy(char *old, char c)
{
	size_t 		cur_size;
	char		*young;

	cur_size = ft_strlen(old);
	if (!(young = calloc(cur_size+2, 1)))
		exit_error("Malloc error", 1);
	ft_strlcpy(young, old, cur_size+1);
	young[cur_size] = c;
	free(old);
	return (young);
}
