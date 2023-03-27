#include "../includes/minishell.h" 
#include "../libft/libft.h"

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
	char	line[1000] = "echo 'hola muy buenas'|grep hola|wc -w > outfile.txt";

	if (argc == 0 || !argv)
		return (1);
	tokens = NULL;
	lst_split(&tokens, line, '|');
	return (0);
}

