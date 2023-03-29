#include "../includes/minishell.h" 
#include "../libft/libft.h"

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