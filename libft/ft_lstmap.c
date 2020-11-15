/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <iadrien@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:02:42 by iadrien           #+#    #+#             */
/*   Updated: 2020/05/23 18:41:27 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_list;
	t_list		*new_list_backup;
	void		*test_content;

	new_list_backup = ((void*)0);
	while (lst && f)
	{
		test_content = f(lst->content);
		if (!(new_list = ft_lstnew(test_content)))
		{
			ft_lstclear(&new_list_backup, del);
			free(test_content);
			return ((void*)0);
		}
		ft_lstadd_back(&new_list_backup, new_list);
		lst = lst->next;
	}
	return (new_list_backup);
}
