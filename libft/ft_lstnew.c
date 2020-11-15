/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:01:03 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/23 18:41:58 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*new_list;

	if (!(new_list = malloc(sizeof(t_list))))
		return ((void*)0);
	new_list->content = (void*)content;
	new_list->next = ((void*)0);
	return (new_list);
}
