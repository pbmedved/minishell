/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:56:49 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:57:02 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;

	if (dst == ((void*)0) && src == ((void*)0))
		return ((void*)0);
	s = (char *)src;
	d = (char *)dst;
	if (dst < src)
		while (n-- > 0)
		{
			*d++ = *s++;
		}
	else
	{
		s += n - 1;
		d += n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	return (dst);
}
