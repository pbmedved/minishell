/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:04:05 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/06 14:41:50 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *res_under;

	if (!*lst)
		return ;
	while (*lst)
	{
		res_under = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = res_under;
	}
	*lst = ((void*)0);
}
