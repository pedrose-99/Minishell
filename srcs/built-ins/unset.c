#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

void	unset(t_list	*tokens, t_list	**env)
{
	t_list	*to_delete;

	to_delete = find_node_by_key(*env, (char *)tokens->content);
	delete_node(env, to_delete);	
}

int	main(int argc, char **argv, char **env)
{
	t_list	*env_lst;
	t_list	*unset_lst;

	if (argc != 1)
		return (1);
	if (!argv)
		return (2);
	env_lst = NULL;
	set_env_list(&env_lst, env);
	print_env_lst(env_lst);
	printf("\n\n\n\n\n\n");
	ft_lstadd_back(&unset_lst, ft_lstnew((void *)"unset"));
	ft_lstadd_back(&unset_lst, ft_lstnew((void *)"USER"));
	unset(unset_lst->next, &env_lst);
	print_env_lst(env_lst);
	printf("\n\n\n\n\n\n");
}