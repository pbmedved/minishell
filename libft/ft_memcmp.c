/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:58:42 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:58:53 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)buf1;
	mem2 = (unsigned char *)buf2;
	while (n-- > 0)
	{
		if (*mem1 > *mem2 || *mem1 < *mem2)
			return (*mem1 - *mem2);
		mem1++;
		mem2++;
	}
	return (0);
}
