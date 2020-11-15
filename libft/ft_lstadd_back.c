/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:06:05 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/21 12:46:56 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*res;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
	}
	else
	{
		res = *lst;
		while (res->next != ((void*)0))
			res = res->next;
		res->next = new;
	}
}
