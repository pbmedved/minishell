/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:32:16 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 17:16:26 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	new_string;

	i = ft_strlen(dst);
	new_string = i + ft_strlen(src);
	if (size < i)
		return (size + ft_strlen(src));
	size -= i;
	while (*src != '\0' && size > 1)
	{
		dst[i++] = *src;
		src++;
		size--;
	}
	dst[i++] = '\0';
	return (new_string);
}
