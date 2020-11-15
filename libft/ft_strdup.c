/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:35:38 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:49:33 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *str)
{
	char	*dup;

	if (!(dup = malloc(sizeof(*str) * (ft_strlen(str) + 1))))
		return (0);
	ft_strlcpy(dup, str, ft_strlen(str) + 1);
	return (dup);
}
