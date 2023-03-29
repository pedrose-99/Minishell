#include "../includes/minishell.h" 
#include "../libft/libft.h"

int	check_str_dict(char *str, char **dict, int *start)
{
	int	cont2;
	int	word;

	while (str[*start])
	{
		word = 0;
		while (dict[word])
		{
			cont2 = 0;
			if (dict[word][cont2] == str[*start])
			{
				while (dict[word][*start + cont2]
					&& dict[word][*start + cont2] == str[cont2])
						cont2++;
				if (dict[word][cont2] == '\0')
					return (word);
			}
			word++;
		}
		(*start)++;
	}
	return (-1);
}

int	end_parenthesis(char *str, int start)
{
	int	open_par;
	int	close_par;
	int	i;

//" (   echo (grep hola a | grep (echo hola | wc -w)) | grep hola|wc -w > outfile.txt )  "
	open_par = 0;
	close_par = 0;
	i = start;
	while (str[i])
	{
		if (str[i] == '(')
			open_par++;
		if (str[i] == ')')
			close_par++;
		if (open_par == close_par)
			break ;
		i++;
	}
	return (i);
}

int	operators(t_nodo **tree, t_list **stack)
{
	int		i;
	char	*line;
	char	*left;
	char	*right;

	i = 0;
	line = (char*)(*stack)->content;
	printf("%s\n", line);
	//printf("%s\n", line);
	while (line[i])
	{
		if (line[i] == '(')
			i = end_parenthesis(line, i);
		if ((line[i] == '&' && line[i + 1] == '&')
			|| (line[i] == '|' && line[i + 1] == '|'))
		{
			//add_left_node(leaf, ft_substr(line, 0, i));
			left = ft_substr(line, 0, i);
			//printf("Izquierda: %s\n", left);
			int	start_op = i;
			while (line[i] == '&' || line[i] == '|' || line[i] == ' ')
				i++;
			(*tree)->cadena = ft_strdup(ft_substr(line, start_op, i - start_op));
			printf("%s\n", (*tree)->cadena);
			right = ft_substr(line, i, ft_strlen(line) - i);
			//printf("Derecha: %s\n", right);
			delete_node(stack, find_node(*stack, line));
			ft_lstadd_front(stack, ft_lstnew((void *)right));
			ft_lstadd_front(stack, ft_lstnew((void *)left));
			//add_right_node(leaf, ft_substr(line, i, ft_strlen(line) - i));
			return (1);
		}
		else if (line[i] == '|')
		{
			//add_left_node(leaf, ft_substr(line, 0, i));
			left = ft_substr(line, 0, i);
			//printf("Izquierda: %s\n", left);
			(*tree)->cadena = ft_strdup("|");
			printf("%s\n", (*tree)->cadena);
			right = ft_substr(line, i + 1, ft_strlen(line) - i + 1);
			//printf("Derecha: %s\n", right);
			delete_node(stack, find_node(*stack, line));
			ft_lstadd_front(stack, ft_lstnew((void *)right));
			ft_lstadd_front(stack, ft_lstnew((void *)left));
			//add_right_node(leaf, ft_substr(line, i, ft_strlen(line) - i));
			return (1);
		}
			i++;
	}
	//printf("Sale del bucle, no encontró operadores\n");
	return (0);	
}

int	parenthesis(t_nodo **tree, t_list **stack)
{
	int		i;
	char	*line;
	char	*left;
	char	*right;

	i = 0;
	line = (char *)(*stack)->content;
	printf("%s\n", line);
	//printf("%s\n", line);
	while (line[i])
	{
		if (line[i] == '(')
		{
			//add_left_node(leaf, ft_substr(line, 0, i));
			left = ft_substr(line, 0, i - 1);
			//printf("Izquierda: %s\n", left);
			printf("()\n");
			(*tree)->cadena = ft_strdup("()");
			right = ft_substr(line, i + 1, end_parenthesis(line, i) - (i + 1));
			//printf("Derecha: %s\n", right);
			delete_node(stack, find_node(*stack, line));
			ft_lstadd_front(stack, ft_lstnew((void *)right));
			ft_lstadd_front(stack, ft_lstnew((void *)left));
			//add_right_node(leaf, ft_substr(line, i, ft_strlen(line) - i));
			return (1);
		}
		i++;
	}
	//printf("Sale del bucle, no encontró paréntesis\n");
	return (0);	
}

void	binary_tree(char *line)
{
	t_list	*stack;
	t_nodo	*tree;
	int		check;
	char 	*curr_line;

	ft_lstadd_front(&stack, ft_lstnew((void *)line));
	while (stack)
	{
		check = 0;
		check += operators(&tree, &stack);
		check += parenthesis(&tree, &stack);
		if (check == 0)
		{
			curr_line = (char *)stack->content;
			//printf("Va a borrar el nodo\n");
			delete_node(&stack, find_node(stack, curr_line));
		}
		sleep(2);
	}
}

void	lst_split(t_list **lst, char *line, int c)
{
	int		start;
	int		end;
	char	*token;

	end = 0;
	while (line[end] && line[end] == c)
		end++;
	while (line[end])
	{
		start = end;
		while (line[end] && line[end] != c)
			end++;
		token = ft_substr(line, start, end - start);
		ft_lstadd_back(lst, ft_lstnew((void *)token));
		token = (char *)ft_lstlast(*lst)->content;
		printf("Token es %s$\n", token);
		while (line[end] && line[end] == c)
			end++;
	}
}

char	*eliminate_parenthesis(char *str)
{
	int		i;
	int		start;
	int		end;
	int		par1;

	i = 0;
	par1 = 0;
	while (str[i])
	{
		if (str[i] == '(' && par1 == 0)
		{
			start = i + 1;
			par1++;
		}
		else if (str[i] == ')')
		{
			end = i;
			while (str[i])
			{
				if (str[i] == ')')
					end = i;
				i++;
			}
			return (ft_substr(str, start, end - start));
		}
		i++;
	}
	return (NULL);
}

int	main_operators(char *str)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	while (str[i])
	{
		if (str[i] == '|')
			op++;
		if (str[i] == '(')
		{
			while (str[i] != ')')
				i++;
		}
		else if (str[i] == '|' && str[i + 1] == '|')
			op++;
		else if (str[i] == '&' && str[i + 1] == '&')
			op++;
		i++;
	}
	return (op);
}

int	main(int argc, char **argv)
{
	t_list	*tokens;
	char	*line;
	t_list	*stack;

	line = malloc(sizeof(1000));
	if (argc == 0 || !argv)
		return (1);
	tokens = NULL;
	stack = NULL;
	line = ft_strdup("echo (grep hola a | grep (echo hola | wc -w)) | grep hola && wc -w > outfile.txt");
	printf("%s\n", line);
	binary_tree(line);
	return (0);
}

