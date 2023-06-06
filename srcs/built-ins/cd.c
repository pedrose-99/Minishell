#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

char	*aux_join_variadic(int n, ...)
{
	va_list	lst;
	int		cont;
	char	*join;

	va_start(lst, n);
	cont = 0;
	join = va_arg(lst, char *);
	while (cont < n)
	{
		join = aux_join(join, va_arg(lst, char *)); //cambiar por aux_join para liberar char* alocados con malloc,
													// hacer otra función para ese caso, y esta solo para pasar str literals
													//o usar strdup para que haga una copia del str con malloc
		cont++;
	}
	va_end(lst);
	printf("Join: %s\n", join);
	return (join);
}

void	cd(char *path, t_list	**env_lst)
{
	char	*path_to_move;
	t_list	*pwd_env;
	t_kv	*key_value;

	if (path[0] == '/') //path absoluto
		path_to_move = path;
	else //path relativo
	{
		path_to_move = NULL;
		path_to_move = getcwd(path_to_move, 100000);
		/*path_to_move = aux_join(path_to_move, "/"); //hacer una función variadica para que haga el join de múltiples strings en una sola función
		path_to_move = aux_join(path_to_move, path);
		*/
		aux_join_malloc_variadic(2, path_to_move, "/", path);
	}
	if (chdir(path_to_move) == 0)
	{
		//esto cambiarlo por función de resetar valor de una variable de entorno
		set_env_value(env_lst, "OLD_PWD", get_env_value(*env_lst, "PWD"));
		set_env_value(env_lst, "PWD", path_to_move);
	}
	else
		printf("cd: no such file or directory: %s\n", path);
}

int	main(void)
{
	aux_join_variadic(3, "hola ", "buenas ", "jeje ", "   .");
	return (0);
}