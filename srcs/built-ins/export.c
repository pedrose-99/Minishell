#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

/*static void	check_export3(t_list	*env_lst, char	*token_content)
{
	int		cont_key;
	int		cont_value;
	char	*key;
	char	*value;

	cont_key = 0;
	while (token_content[cont_key])
	{
		if (token_content[cont_key] == '['
			&& token_content[cont_key + 1] == '=')
		{
			key = ft_substr(token_content, 0, cont_key - 1);
			cont_value = cont_key + 2;
			while (token_content[cont_value])
			{
				if (token_content[cont_value] == ']'
					&& token_content[cont_value] == '\0')
						value = ft_substr(token_content, cont_key, cont_value - 1);
				cont_value++;
			}
		}
		cont_key++;
	}
	if (key && value)
		ft_lstadd_back(&env_lst, ft_lstnew((void *) set_key_value(key, value)));
}
*/

void	swap_nodes(t_list *node1, t_list *node2)
{
	void	*aux;

	aux = node1->content;
	node1->content = node2->content;
	node2->content = aux;
}

//export devuelve la lista ordenada alfabéticamente - hacer función de ordenación
void	sort_env_lst(t_list	**lst)
{
	t_kv	*key_value;
	char	*key_1;
	char	*key_2;
	t_list	*curr1;
	t_list	*curr2;

	curr1 = *lst;
	curr2 = curr1;
	while (curr1)
	{
		while (curr2)
		{
			//cambiar esto por funcion de get_key_value - asegurarse que funciona bien
			key_value = (t_kv *)curr1->content;
			key_1 = get_env_key(curr1);
			key_value = (t_kv *)curr2->content;
			key_2 = key_value->key;
			if (ft_strncmp(key_1, key_2, longer_str(key_1, key_2)) > 0)
				swap_nodes(curr1, curr2);
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
		if (!curr1->next)
			break ;
		curr2 = curr1->next;
	}
}

void	export(t_list	*tokens, t_list *env_lst)
{
	t_list	*node;

	if (ft_lstsize(tokens) == 1)
	{
		sort_env_lst(&env_lst);
		print_env_lst(env_lst);
	}
	else if (ft_lstsize(tokens) > 1)
	{
		while (tokens)
		{
			node = set_env_node((char *)tokens->content);
			if (node)
				ft_lstadd_back(&env_lst, node);
			tokens = tokens->next;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list	*env_lst;
	t_list	*export_lst;

	if (argc != 1 && !argv)
		return (1);
	env_lst = NULL;
	set_env_list(&env_lst, env);
	ft_lstadd_back(&export_lst, ft_lstnew((void *)"export"));
	export(export_lst, env_lst);
	return (0);
}
