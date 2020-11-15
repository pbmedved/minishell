/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:59:00 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/26 19:19:53 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	while (n-- > 0)
	{
		if (*(unsigned char*)arr == (unsigned char)c)
			return ((void*)arr);
		arr++;
	}
	return ((void*)0);
}
