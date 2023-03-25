#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

//la uso echo: cuando encuentra un dolar coge el texto antes de un espacio (la key) y devuelve su valor en la lista de env
static char	*get_var_in_str(t_list *lst, char *text)
{
	char	*var;
	int		cont;

	cont = 0;
	if (text[cont] == '$')
		text++;
	while (text[cont] && text[cont] != ' ')
		cont++;
	var = ft_substr(text, 0, cont);
	return (get_env_value(lst, var));
}

static void	print_env_value(t_list	*env, char	*token, int *pos)
{
	char	*var;

	var = get_var_in_str(env, token);
	if (var)
	{
		printf("%s", var);
		free(var);
	}
	while (token[*pos] && token[*pos] != ' ')
		(*pos)++; //mueve el puntero al final para que luego en echo retome después del nombre de la variable
}

static void	print_wildcards(char *token, int *pos)
{
	wildcards(token);
	while (token[*pos] && token[*pos] != ' ')
		(*pos)++;
}

static void	checker_echo(t_list	*env, char	*token, int *pos)
{
	if (token[*pos] == '$')
		print_env_value(env, token, pos);
	else if (token[*pos] == '*') // dentro de wildcards mover el puntero una posición, para que no coja el *
	{
		(*pos)++;
		print_wildcards(token, pos); 
	}
}

static int	is_str_in_lst(t_list *lst, char *cmp)
{
	while (lst)
	{
		if (ft_strncmp((char *)lst->content, cmp,
				longer_str((char *)lst->content, cmp)) == 0)
					return (1);
		lst = lst->next;
	}
	return (0);
}
//imprime el str de cada token; si tiene un dolar, imprime valor de esa variable si existe; también hacer wildcard si tiene un *
void	echo(t_list *tokens, t_list *env) //plantearlo de manera similar al ft_printf
{
	char	*value;
	int		cont;

	while (tokens)
	{
		value = (char *)tokens->content;
		cont = 0;
		while (value[cont])
		{
			checker_echo(env, value, &cont);
			if (value[cont])
			{
				printf("%c", value[cont]);
				cont++;
			}
		}
		if (tokens->next)
			printf(" ");
		tokens = tokens->next;
	}
	if (is_str_in_lst(tokens, "-n") == 0)
		printf("\n");
}

int	main(int argc, char **argv, char **env)
{
	t_list	*echo_lst;
	t_list	*env_lst;

	if (argc < 1 && !argv)
		return (1);
	echo_lst = NULL;
	env_lst = NULL;
	set_env_list(&env_lst, env);
	print_env_lst(env_lst);
	ft_lstadd_back(&echo_lst, ft_lstnew((void *)"$USER"));
	ft_lstadd_back(&echo_lst, ft_lstnew((void *)"*.a"));
	echo(echo_lst, env_lst);
	return (0);
}
