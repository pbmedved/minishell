/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:13:03 by iadrien           #+#    #+#             */
/*   Updated: 2020/11/15 11:43:02 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	int		it;
	int		i;

	i = 0;
	if (s1 == (void*)0 || set == (void*)0)
		return ((void*)0);
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		s1++;
	if (*s1 == '\0')
		return (ft_calloc(1, 1));
	it = ft_strlen(s1) - 1;
	while (it >= 0 && ft_strchr(set, s1[it]))
		it--;
	return (ft_substr(s1, 0, it + 1));
}
