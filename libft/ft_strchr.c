/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:36:59 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/02 16:37:00 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
