/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/03/25 11:00:23 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

//borra un nodo de una lista
void	delete_node(t_list **lst, t_list	*node)
{
	t_list	*curr;
	t_list	*prev;
	t_kv	*curr_kv;
	t_kv	*node_kv;

	curr = *lst;
	prev = *lst;
	curr_kv = (t_kv *)curr->content;
	node_kv = (t_kv *)node->content;
	printf("Nodo a comparar: %s\n", node_kv->key);
	while (curr)
	{
		curr_kv = (t_kv *)curr->content;
		printf("Key a comparar: %s\n", curr_kv->key);
		if (ft_strncmp(curr_kv->key, node_kv->key, longer_str(curr_kv->key, node_kv->key)) == 0)
		{
			printf("Coinciden\n");
			prev->next = curr->next;
			free(curr_kv->key);
			free(curr_kv->value);
			free(curr_kv);
			node->next = NULL;
			free(node);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("\n\n\n\n");
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
		curr = curr->next;
	}
}
