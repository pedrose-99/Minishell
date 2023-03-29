# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
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


typedef struct s_nodo
{
	char 			*cadena;
	struct s_nodo 	*izquierda;
	struct s_odo 	*derecha;
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
void	delete_node_str(t_list **lst, t_list *node);
void	remove_head(t_list **lst);
t_list	*find_node(t_list *lst, char *str);
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

//binary tree
int 	ft_strcmp(char *s1, char *s2);
char 	*ft_strcpy(char *s1, char *s2);
t_nodo 	*nuevo_nodo(char cadena[1000]);
void	add_left_node(t_nodo **nodo, char *cadena);
void	add_right_node(t_nodo **nodo, char *cadena);
t_nodo 	*buscar(t_nodo *nodo, char *cadena);
void	print_arbol(t_nodo *nodo);