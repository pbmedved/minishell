/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:35:12 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/28 13:13:39 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		i;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == (void*)0 || s2 == (void*)0)
		return ((void*)0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (SIZE_MAX - 1 - len_s1 < len_s2)
		return ((void*)0);
	if (!(sjoin = (char*)malloc(((len_s1 + len_s2 + 1) * sizeof(char)))))
		return ((void*)0);
	i = 0;
	while (*s1 != '\0')
		sjoin[i++] = *s1++;
	while (*s2 != '\0')
		sjoin[i++] = *s2++;
	sjoin[i] = '\0';
	return (sjoin);
}
