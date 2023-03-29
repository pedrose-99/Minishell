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
