#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	shell_vars_file(t_list *env_lst)
{
	int		fd;
	int		pid;
	char	**set;
	t_list	*path;
	t_kv	*key_value;
	char	**path_matrix;
	char	*path_cmd;
	int		cont;

	fd = open(".shellvars", O_CREAT | O_WRONLY);
	set = malloc(sizeof(char *) * 2);
	set[0] = "set";
	set[1] = NULL;
	path = find_node_by_key(env_lst, "PATH");
	key_value = (t_kv *)path->content;
	path_matrix = ft_split(key_value->value, ':');
	cont = 0;
	while (path_matrix[cont])
	{
		path_cmd = aux_join(path_matrix[cont], "/set");
		printf("Path del comando a probar: %s\n", path_cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			printf("Comando correcto: %s\n", path_cmd);
			free(path_cmd);
			break ;
		}
		free(path_cmd);
		cont++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		if (execve(path_cmd, set, NULL) < 0)
			exit(0);
	}
}

void	shell_var_lst(t_list **lst)
{
	int		fd;
	char	*line;

	fd = open(".shellvars", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("Línea es: %s\n", line);
		ft_lstadd_back(lst, set_env_node(line));
		free(line);
		line = get_next_line(fd);
	}
	unlink(".shellvars");
}

int	main(int argc, char **argv, char **env)
{
	t_list	*var_lst;
	t_list	*env_lst;

	if (argc == 0 || !argv)
		return (1);
	set_env_list(&env_lst, env);
	//print_env_lst(env_lst);
	shell_vars_file(env_lst);
	shell_var_lst(&var_lst);
	print_env_lst(var_lst);
	return (0);
}

