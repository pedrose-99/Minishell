# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <errno.h>
#include "../libft/libft.h"

typedef struct s_kv
{
	char *key;
	char *value;
}	t_kv;

typedef struct s_key_new
{
	char *key;
	char **value;
}	t_key_new;

typedef struct s_nodo
{
	char cadena[1000];
	struct s_nodo *izquierda;
	struct s_odo *derecha;
} 				t_nodo;


// Esta estructura se usara para guardar la informacion pasada por el terminal.
typedef struct s_input_inf
{
	char *line;
	int num_comandos;
	//Struct s_nodo?
}				t_input_inf;


//lst functions
t_kv	*set_key_value(char *key, char *value);
void	delete_node(t_list **lst, t_list	*node);
t_list	*move_to_node(t_list	*lst, int pos);

//env lst functions
t_kv	*set_key_value(char *key, char *value);
t_list	*set_env_node(char *env_var);
void	set_env_list(t_list	**env_lst, char **env);
void	print_env_lst(t_list *env_lst);
void	print_str_lst(t_list *str_list);
char	*get_env_key(t_list	**lst, t_list **node);
char	*get_env_value(t_list	*lst, char *cmp);
t_list	*get_node_by_key(t_list	*lst, char *cmp);
void 	set_env_value(t_list **env_lst, char *key, char *new_value);

//built-ins
void	cd(char *path, t_list	**env_lst);
void	echo(t_list *tokens, t_list *env);
void	export(t_list	*tokens, t_list *env_lst);
void 	pwd(t_list	*env_lst);
void	unset(t_list	*tokens, t_list	**env);
void	b_exit(void);

void	wildcards(char *cmp);