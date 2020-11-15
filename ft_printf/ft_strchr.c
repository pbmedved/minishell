/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:36:59 by iadrien           #+#    #+#             */
/*   Updated: 2020/07/15 16:32:10 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return ((char*)str);
		str++;
	}
	if (*str == ch)
		return ((char*)str);
	return (((void*)0));
}
