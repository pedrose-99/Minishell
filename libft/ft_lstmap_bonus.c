/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 17:04:17 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*head_new;

	if (!lst || !f || !del)
		return (0);
	new_node = ft_lstnew(f(lst->content));
	if (new_node == NULL)
		return (0);
	head_new = new_node;
	lst = lst->next;
	while (lst)
	{
		new_node->next = ft_lstnew(f(lst->content));
		if (new_node->next == NULL)
		{
			ft_lstclear(&head_new, del);
			return (0);
		}
		lst = lst->next;
		new_node = new_node->next;
	}
	new_node->next = NULL;
	return (head_new);
}
