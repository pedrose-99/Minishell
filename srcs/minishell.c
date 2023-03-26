#include "../includes/minishell.h"
#include "../libft/libft.h"
/*
void	handle_ctr_c(t_input_inf *info)
{
	free(info->line);
	info->line = ft_strdup("");
	info->num_comandos = 0;
	ft_putstr_fd("\n", STDIN); (o STDIN_FILENO)
	llamar a funcion que te escriba minisell> 
		line = readline("minishell> ");
		add_history(line);
}

*/
void	signal_handler(int signal)
{
	int	pid;

	pid = getpid();
	printf("ID de proceso actual: %d\n", pid);
	printf("Valor numérico de señal: %d\n", signal);
	if (signal == SIGINT)
	{
		printf("Interceptó SIGINT o CTRL + C\n");
		readline("minishell> ");
	}
	else if (signal == SIGTSTP)
	{
		printf("Interceptó SIGSTP o CTRL + Z\n");
		kill(pid, SIGSTOP);
	}
	else if (signal == SIGQUIT)
	{
		printf("Interceptó SIGQUIT o CTRL + BARRA \n");
		exit(1);
	}
}

void	set_env_list(t_list *lst_env, char **env)
{
	int			row;
	int			col;
	char		*key;
	char		*value;
	t_kv		*key_value;
	t_kv 		*kv_ptr;

	row = 0;
	col = 0;
	while (env[row])
	{
		while (env[row][col])
		{
			if (env[row][col] == '=')
			{
				key = ft_substr(env[row], 0, col);
				value = ft_substr(env[row], col + 1, ft_strlen(env[row]) - col);
				key_value = set_key_value(key, value);
				ft_lstadd_back(&lst_env, ft_lstnew(&key_value));
				kv_ptr = (t_kv *)(ft_lstlast(lst_env)->content);
				key_value = kv_ptr;
				printf("Key de nodo actual: %s\n", key_value->key);
				printf("Valor de nodo actual: %s\n", key_value->value);
				printf("\n\n");
				break ;
			}
				col++;
		}
		row++;
		col = 0;
	}
}

void	lst_split(t_list **lst, char *line)
{
	int		start;
	int		end;
	char	*token;
	int		cont;

	end = 0;
	while (line[end] && (line[end] == ' '))
		end++;
	start = end;
	while (line[end])
	{
		while (line[end] && line[end] != ' ')
			end++;
		token = malloc(end - start);
		cont = 0;
		while (line[start] && start < end)
		{
			token[cont] = line[start];
			cont++;
			start++;
		}
		token[cont] = '\0';
		ft_lstadd_back(lst, ft_lstnew((void *)token));
		token = (char *)ft_lstlast(*lst)->content;
		printf("%s$\n", token);
		while (line[end] && line[end] == ' ')
			end++;
		start = end;
	}
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sa;
	char				*line;
	t_list				*env_lst;
	t_list				*tokens;

	if (argc != 1)
		return (1);
	if (!argv)
		return (2);
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_lst = NULL;
	tokens = NULL;
	set_env_list(env_lst, env);
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		printf("Línea leída: %s\n", line);
		lst_split(&tokens, line);
		free(line);
	}
	
	system("leaks minishell");
	return (0);
}
