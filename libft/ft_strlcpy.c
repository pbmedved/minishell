/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:30:56 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:32:10 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	int i;

	if (dst == (void*)0 || src == (void*)0)
		return (0);
	i = ft_strlen(src);
	while (size != 0 && size > 1 && *src != '\0')
	{
		*dst++ = *src++;
		size--;
	}
	if (size)
		*dst = '\0';
	return (i);
}
