/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:54:20 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/06 14:31:14 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *memptr, int val, size_t num)
{
	unsigned char	*p;

	p = (unsigned char*)memptr;
	while (num-- > 0)
	{
		*p = (unsigned char)val;
		p++;
	}
	return (memptr);
}
