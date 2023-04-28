#include "../includes/minishell.h" 
#include "../libft/libft.h"

/*if (entry->d_type == DT_REG)
			printf("File: %s\n", entry->d_name);
		else if (entry->d_type == DT_DIR)
			printf("Directory: %s\n", entry->d_name);
		*/

static int	ft_rev_strncmp(char *s1, char *s2, int n)
{
	int	cont_s1;

	cont_s1 = (int)ft_strlen(s1) - 1;
	while (n >= 0)
	{
		if (s1[cont_s1] != s2[n])
			return ((unsigned char)s1[cont_s1] - (unsigned char)s2[n]);
		cont_s1--;
		n--;
	}
	return (0);
}

size_t	shorter_str(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len < s2_len)
		return (s1_len);
	return (s2_len);
}

static void	match_wildcards(char *entry, char *cmp, int *space)
{
	cmp++;
	if (ft_strlen(entry) >= ft_strlen(cmp))
	{
		if (ft_rev_strncmp(entry, cmp, (int)ft_strlen(cmp) - 1) == 0
			&& entry[0] != '.')
		{
			if ((*space)++ > 0)
				printf(" ");
			printf("%s", entry);
		}
	}
}

void	wildcards(char *cmp)
{
	//puntero al directorio
	DIR				*dir;
	//informacion sobre el archivo que se esta sacando a cada momento
	struct dirent	*entry;
	int				space;

	space = 0;
	//empezamos a leer el directorio sintener en cuenta los .DS etc
	dir = opendir(".");
	//
	entry = readdir(dir);
	while (entry)
	{
		match_wildcards(entry->d_name, cmp, &space);
		entry = readdir(dir);
	}
	closedir(dir);
}

/*
Funcion wildcards:

1.  si solo hay delante del *hay un caracter valido:
2. si solo hay detras del *un caracter valido
3. Si hay delante y detras un caracter valido
4. Si tienes un archivo que se llame pepe y pongo pepe*e sale mal pero si pongo pep*e sale bien o pe*e tambien da bien

*/


int	main(int argc, char **argv, char **env)
{
	t_list	*wildcard_lst;
	t_list	*env_lst;

	if (argc != 1)
		return (1);
	if (!argv)
		return (2);
	set_env_list(&env_lst, env);
	ft_lstadd_back(&wildcard_lst, ft_lstnew((void *)".a"));
	ft_lstadd_back(&wildcard_lst, ft_lstnew((void *)".out"));
	wildcards(wildcard_lst);
	return (0);
}

