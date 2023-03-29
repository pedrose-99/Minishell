/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/03/29 18:33:36 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

//borra un nodo de una lista
void	delete_node(t_list **lst, t_list	*node)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	prev = *lst;
	if (curr && ft_strncmp((char *)curr->content, (char *)node->content,
			longer_str((char *)curr->content, (char *)node->content)) == 0)
	{
    	*lst = curr->next;
    	free(curr);
        return  ;
    }
	while (curr)
	{
		if (ft_strncmp((char *)curr->content, (char *)node->content,
				longer_str((char *)curr->content, (char *)node->content)) == 0)
		{
			prev->next = curr->next;
			free(curr->content);
			curr->next = NULL;
			free(curr);
			curr = NULL;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_list	*find_node(t_list *lst, char *str)
{
	while (lst)
	{
		if (ft_strncmp((char *)lst->content, str,
				longer_str((char *)lst->content, str)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
void	delete_node_str(t_list **lst, t_list *node)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	while (curr)
	{
		if (ft_strncmp((char *)curr->content, (char *)node->content,
				longer_str((char *)curr->content, (char *)node->content)) == 0)
		{
			prev->next = curr->next;
			free(curr->content);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	remove_head(t_list **lst)
{
	t_list	*first_node;
	t_list	*second_node;

	first_node = *lst;
	second_node = (*lst)->next;
	(*lst)->next = NULL;
	*lst = second_node;
	free(first_node->content);
	free(first_node);
}

//busca un nodo con una posición y lo devuelve
t_list	*move_to_node(t_list	*lst, int pos)
{
	int	cont;

	cont = 0;
	while (cont < pos)
	{
		lst = lst->next;
		cont++;
	}
	return (lst);
}

//imprimir lista con contenido string
void	print_str_lst(t_list *str_list)
{
	char	*content;
	t_list	*curr;

	curr = str_list;
	while (curr)
	{
		content = (char *)curr->content;
		printf("%s\n", content);
		curr = curr->next;
	}
}
