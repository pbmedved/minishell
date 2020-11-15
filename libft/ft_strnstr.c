/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:23:29 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/23 22:23:47 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*new_dst;
	char	*new_point;
	size_t	l;

	l = ft_strlen(little);
	if (ft_strlen(big) <= len)
		len = ft_strlen(big);
	new_dst = (char*)big;
	while (len >= l)
	{
		new_point = (char*)little;
		if (ft_strncmp(new_dst, new_point, l) == 0)
			return (new_dst);
		new_dst++;
		new_point++;
		len--;
	}
	return (0);
}
