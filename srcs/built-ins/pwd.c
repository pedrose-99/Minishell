#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

void pwd(t_list	*env_lst)
{
	char 	*pwd_str;

	pwd_str = NULL;
	pwd_str = getcwd(pwd_str, 100000);
	if (pwd_str)
	{
		printf("%s\n", pwd_str);
		set_env_value(env_lst, "PWD", pwd_str);
	}
	else
		printf("Devolvió pwd null\n");
}