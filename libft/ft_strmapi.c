/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:26:22 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/21 15:01:46 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	int		i;

	if (!s || !f)
		return ((void*)0);
	i = -1;
	if (!(mapi = (char*)malloc((ft_strlen(s) + 1) * sizeof(char))))
		return ((void*)0);
	while (++i != (int)ft_strlen(s))
		mapi[i] = f(i, s[i]);
	mapi[i] = '\0';
	return (mapi);
}
