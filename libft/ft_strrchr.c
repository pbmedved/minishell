/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:23:07 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/28 13:46:13 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *str, int ch)
{
	size_t		n;

	n = ft_strlen(str);
	str += n;
	while (*str == ch || n > 0)
	{
		if (*str == ch)
			return ((char*)str);
		str--;
		n--;
	}
	return ((void*)0);
}
