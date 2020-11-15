/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:11:12 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/28 13:11:07 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t num, size_t size)
{
	void	*allocated;

	if ((num != 0 && SIZE_MAX / num < size) \
	|| (size != 0 && SIZE_MAX / size < num))
		return ((void*)0);
	if (!(allocated = malloc(num * size)))
		return ((void*)0);
	ft_memset(allocated, 0, num * size);
	return (allocated);
}
