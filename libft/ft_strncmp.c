/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:24:47 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/05 22:28:18 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n-- > 0)
	{
		if ((unsigned char)*str1 == '\0' || (unsigned char)*str2 == '\0' \
		|| ((unsigned char)*str1 != (unsigned char)*str2))
		{
			if ((unsigned char)*str1 == (unsigned char)*str2)
				return (0);
			return ((unsigned char)*str1 - (unsigned char)*str2 > 0 ? 1 : -1);
		}
		str1++;
		str2++;
	}
	return (0);
}
