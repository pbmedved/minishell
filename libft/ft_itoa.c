/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:06:49 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/19 21:14:20 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_numlen(long n)
{
	size_t			len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

char				*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	long			num;

	num = n;
	len = ft_numlen(n);
	if (n < 0)
		len++;
	if (!(str = (char*)malloc(len + 1 * sizeof(char))))
		return ((void*)0);
	str[len--] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n < 0)
		num *= -1;
	if (n == 0)
		str[0] = '0';
	while (num /= 10 > 9)
	{
		str[len--] = num % 10 + 0x30;
		num /= 10;
	}
	return (str);
}
