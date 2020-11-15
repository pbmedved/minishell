/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:57:29 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:58:26 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*p;

	if (dst == ((void*)0) && src == ((void*)0))
		return ((void*)0);
	d = (char *)src;
	p = (char *)dst;
	while (n-- > 0)
		*p++ = *d++;
	return (dst);
}
