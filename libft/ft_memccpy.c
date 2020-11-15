/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:59:31 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/19 20:36:45 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*d;
	char	*p;

	d = (char *)src;
	p = (char *)dst;
	while (n-- > 0 && (unsigned char)*d != (unsigned char)c)
		*p++ = *d++;
	if ((unsigned char)*d == (unsigned char)c)
		*p++ = (unsigned char)*d++;
	else
		return ((void*)0);
	return (p);
}
