#include "includes/minishell.h"
#include "libft/libft.h"

//establece valores de nodo de variable de entorno: key-value
t_kv	*set_key_value(char *key, char *value)
{
	t_key_new	*key_value;
	int i;
	int j;
	int aux;

	i = 0;
	j = 0;
	aux = 0;
	key_value = malloc(sizeof(t_kv));
	key_value->key = key;
	while (value[i])
	{
		aux = 0;
		while(!es_espacio(value[i]) && value[i])
		{
			key_value->value[j][aux] = value[i];
			i++;
			aux++;
		}
		if (es_espacio(value[i]))
		{
			aux = 0;
			j++;
			while(es_espacio(value[i]))
			{
				key_value->value[j][aux] = value[i];
				aux++;
				i++;
			}
		}
	}
	return (key_value);
}



//crear un nodo para lista de variables de entorno
t_list	*set_env_node(char *env_var)
{
	t_kv	*key_value;
	int		cont;

	cont = 0;
	while (env_var[cont])
	{
		if (env_var[cont] == '=')
		{
			key_value = set_key_value(ft_substr(env_var, 0, cont),
					ft_substr(env_var, cont + 1, ft_strlen(env_var) - cont));
			return (ft_lstnew((void *)key_value));
		}
			cont++;
	}
	return (NULL);
}

//crear lista de variables de entorno
void	set_env_list(t_list	**env_lst, char **env)
{
	int			row;
	t_list		*node;

	row = 0;
	while (env[row])
	{
		node = set_env_node(env[row]);
		if (node)
			ft_lstadd_back(env_lst, node);
		row++;
	}
}

//imprimir lista de variables de entorno
void	print_env_lst(t_list *env_lst)
{
	t_kv	*key_value;
	t_list	*curr;
	int		cont;

	cont = 0;
	curr = env_lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		printf("%s=%s\n", key_value->key, key_value->value);
		curr = curr->next;
		cont++;
	}
}

//busca un nodo con una key y la devuelve
char	*get_env_key(t_list	**lst, t_list **node)
{
	t_list	*curr;
	t_kv	*key_value;

	curr = *lst;
	while (curr)
	{
		if (curr == *node)
		{
			key_value = (t_kv *)curr->content;
			return (key_value->key);
		}
		curr = curr->next;
	}
	return (NULL);
}

//busca un nodo con una key y devuelve su valor
char	*get_env_value(t_list	*lst, char *cmp)
{
	t_kv	*key_value;
	char	*key;
	t_list	*curr;

	printf("\nHOLOOO\n");
	curr = lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		key = key_value->key;
		if (ft_strncmp(cmp, key, longer_str(key, cmp)) == 0)
			return (key_value->value);
		curr = curr->next;
	}
	return (NULL);
}

//busca un nodo con una key y lo devuelve
t_list	*get_node_by_key(t_list	*lst, char *cmp)
{
	t_kv	*key_value;
	char	*key;
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		key_value = (t_kv *)curr->content;
		key = key_value->key;
		if (ft_strncmp(cmp, key, longer_str(key, cmp)) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
//establece el valor de un nodo buscando su key
void set_env_value(t_list **env_lst, char *key, char *new_value)
{
	t_list	*env_var;
	t_kv 	*key_value;

	env_var = get_node_by_key(*env_lst, key);
	key_value =	(t_kv *)env_var->content;
	free(key_value->value);
	key_value->value = new_value;
	env_var->content = (void *)key_value;
}