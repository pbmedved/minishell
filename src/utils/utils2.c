/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:46:25 by iadrien           #+#    #+#             */
/*   Updated: 2021/03/22 20:47:55 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_strncmp_revers(char *in, char *this, size_t n)
{
	size_t in_len;
	size_t this_len;

	in_len = ft_strlen(in) - 1;
	this_len = ft_strlen(this) - 1;
	while (n-- > 0)
	{
		if ((unsigned char)in[in_len] == '\0' \
		|| (unsigned char)this[this_len] == '\0' \
		|| ((unsigned char)in[in_len] != (unsigned char)this[this_len]))
		{
			if ((unsigned char)in[in_len] == (unsigned char)this[this_len])
				return (0);
			return ((unsigned char)in[in_len] - \
			(unsigned char)this[this_len] > 0 ? 1 : -1);
		}
		in_len--;
		this_len--;
	}
	return (0);
}
