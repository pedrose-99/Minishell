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
	int	p;

	p = start;
	while (str[start])
	{
		if (str[start] == ')')
		{
			p = start;
			while (str[start])
			{
				if (str[start] == ')')
					p = start;
				start++;
			}
		}
		start++;
	}
	return (p);
}

void	tokenize(t_list **lst, char *line)
{
	int	cont;
	int	end;
	char *token;

	cont = 0;
	end = cont;
	while (line[cont])
	{
		if (line[cont] == '(')
		{
			end = end_parenthesis(line, cont);
			if (end == (int)ft_strlen(line))
				return ;
			printf("Caracter y posición: %c y %d\n", line[end], end);
			token = ft_substr(line, cont + 1, end - cont - 1);
			ft_lstadd_back(lst, ft_lstnew((void *)token));
			cont = end;
		}
			cont++;
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


int	main(int argc, char **argv)
{
	t_list	*tokens;
	char	line[1000] = " (   echo (grep hola a | grep buenas a) | grep hola|wc -w > outfile.txt )  ";
	char	**dict;

	if (argc == 0 || !argv)
		return (1);
	tokens = NULL;
	dict = malloc(sizeof(char *) * 4);
	dict[0] = "|";
	dict[1] = ">";
	dict[2] = "&&";
	dict[3] = NULL;
	tokenize(&tokens, line);
	print_str_lst(tokens);
	//lst_split(&tokens, line, ' ');
	return (0);
}

