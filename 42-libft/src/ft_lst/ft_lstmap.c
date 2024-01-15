/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:27:09 by dagomez           #+#    #+#             */
/*   Updated: 2022/05/17 12:48:21 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*position_new;
	t_list	*position_old;

	if (!lst)
		return (0);
	new_lst = ft_lstnew((*f)(lst->content));
	if (!new_lst)
		return (0);
	position_new = new_lst;
	position_old = lst->next;
	while (position_old)
	{
		position_new->next = ft_lstnew((*f)(position_old->content));
		if (!(position_new->next))
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		position_new = position_new->next;
		position_old = position_old->next;
	}
	return (new_lst);
}
