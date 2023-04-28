#include "libft/libft.h"
#include "includes/minishell.h"
#include <stdio.h>

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
	t_list *lexer; // Esta seria la tabla que contiene todos los datos del lexer // Numero de comandos

}				t_parser;

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while((s1[i] == s2[i]) && (s1[i] && s2[i]))
		i++;
	return((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	init_parser(t_parser *parser)
{
	parser->line = (char *)malloc(sizeof(char ));
	parser->line = "";
}

int condition_parentesis(char *line, int i)
{
	int aux_abierto;
	int aux_cerrado;

	aux_abierto = 1;
	aux_cerrado = 0;
	while(aux_abierto != aux_cerrado)
	{
		if (line[i] == '(')
			aux_abierto++;
		if (line[i] == ')')
			aux_cerrado++;
		i++;
	}
	i--;
	return (i);
}

int	saltar_espace(char *line, int i)
{
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return(i);
}

int separar(t_parser *parser)
{
	int i;
	int ancla;
	int parent;

	i = 0;
	ancla = 0;
	while(parser->line[i])
	{
		if(parser->line[i] == '|' || parser->line[i] == '>' || parser->line[i] == '<' || parser->line[i] == '&')
		{
			if(ancla != i)
				ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
			ancla = i;
			if(parser->line[i] == parser->line[i + 1])
			{
				ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, 2)));
				i++;
			}
			else
				ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, 1)));
			i++;
			i = saltar_espace(parser->line, i);
			ancla = i;
		}
		else if (parser->line[i] == '(')
		{
			if(ancla != i)
				ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
			ancla = i;
			i++;
			ancla = i;
			i = condition_parentesis(parser->line, i);
			ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
			i++;
			i = saltar_espace(parser->line, i);
			ancla = i;
			i--;
		}
		i++;
	}
	if (parser->line[i] != ')')
	{
		ft_lstadd_back(&parser->lexer, ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
	}
	return (0);
}

int		check_parentesis(char *line)
{
	int i;
	int parentesis_abierto;
	int parentesis_cerrado;

	i = 0;
	parentesis_abierto = 0;
	parentesis_cerrado = 0;
	while(line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while(line[i] != '"')
				i++;
		}
		else if (line[i] == 39)
		{
			i++;
			while(line[i] != 39)
				i++;
		}
		if (line[i] == '(')
			parentesis_abierto++;
		if (line[i] == ')')
			parentesis_cerrado++;
		i++;
	}
	i = parentesis_abierto - parentesis_cerrado;
	if (i == 0)
		return (1);
	else
		return (0);
}

int 	check_comillas(char *line)
{
	int i;
	int comillas_simples;
	int comillas_dobles;

	i = 0;
	comillas_simples = 0;
	comillas_dobles = 0;
	while(line[i])
	{
		if (line[i] == '"')
			comillas_dobles++;
		if (line[i] == 39)
			comillas_simples++;
		i++;
	}
	if (comillas_simples % 2 == 1 || comillas_dobles % 2 == 1)
		return (0);
	return (1);
}

int check_caract(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			while(line[i] != 39)
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while(line[i] != '"')
				i++;
		}
		else if (line[i] == ',' || line[i] == ';' || line[i] == 92)
			return (0);
		i++;
	}
	return (1);
}

int		check_sintaxis(char *line)
{
	int check_paren;
	int check_other_carac;

	check_other_carac = 0;
	if (check_comillas (line))
	{
		check_paren = check_parentesis(line);
	}
	else
		return (0);
	if (check_paren == 1)
	{
		check_other_carac = check_caract(line);
	}
	else
		return (0);
	if (check_other_carac)
	{
		return (1);
	}
	else
		return (0);
}



void		handle_ctr_c_signal(t_parser *parser)
{
	free(parser->line);
	parser->line = ft_strdup("");
	ft_putstr_fd("^C\n", STDIN_FILENO); //Pasa el comando control c. Otra opcion podria ser hcaer kill al proceso
}

char	**env_list_to_array(t_list *env_list)
{
	char	**env_array;
	char	*content;
	int		i;

	i = 0;
	env_array = (char**)ft_calloc(
	(ft_lstsize(env_list) + 1), sizeof(char*));
	while (env_list)
	{
		content = (char*)env_list->content;
		env_array[i] = content;
		env_list = env_list->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*get_word(char *line, int i)
{
	char *str;
	int ancla;
	int aux;

	i++;
	aux = 0;
	ancla = i;
	printf("\n%c",line[i+1]);
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t') || line[i + 1] == '\0')
		{
			str = (char*)malloc(sizeof(char) * (i - ancla + 1));
			if (!str)
			{
				return (NULL);
			}
			while(ancla < i)
			{
				str[aux] = line[ancla];
				ancla++;
				aux ++;
			}
			if (line[i + 1] == '\0')
			{
				str[aux] = line[ancla];
				aux++;
			}
			str[aux] = '\0';
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	sustituir_dollar(char *line, t_list *env_list)
{
	int i;
	char *new_word;
	char *new_line1;
	char *new_line2;
	int len;

	i = 0;
	len = 0;
	while (line[len])
		len++;
	while (line[i])
	{
		if (line[i] == '$')
		{
			new_word = get_word(line, i);
			new_word = get_env_value(env_list, new_word);
			if (new_word)
			{
				new_line1 = ft_substr(line, 0, i);
				new_line1 = ft_strjoin(new_line1, new_word);
				while(line[i] && (line[i] != ' ' && line[i] != '\t'))
					i++;
				if (line[i])
				{
					new_line2 = ft_substr(line, i, len - 1);
					new_line1 = ft_strjoin(new_line1, new_line2);
				}
				line = ft_strdup(new_line1);
			}
			else
			{
				new_line1 = ft_substr(line, 0, i);
				while(line[i] && (line[i] != ' ' && line[i] != '\t'))
					i++;
				if (line[i])
				{
					new_line2 = ft_substr(line, i, len - 1);
					new_line1 = ft_strjoin(new_line1, new_line2);
				}
				line = ft_strdup(new_line1);
			}
		}
		i++;
		new_word = NULL;
	}
	printf("%s", new_line1);
}

int		hay_palabra_before(char *word_before, char *archivo)
{
	int i;

	i = 0;

	while (word_before[i])
	{
		if (word_before[i] == archivo[i])
			i++;
		else
			return (0);
	}
	return (1);
}

int		hay_palabra_after(char *word_after, char *archivo)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while(archivo[size])
		size++;
	while (word_after[i])
		i++;
	while (i >= 0)
	{
		if (word_after[i] == archivo[size])
		{
			i--;
			size--;
		}
		else
			return (0);
	}
	return (1);
}
char	*get_word_after(char *line, int i)
{
	char *str;
	int ancla;
	int aux;

	i++;
	aux = 0;
	ancla = i;
	if ((line[i] == ' ' || line[i] == '\t') || line[i] == '\0')
		return (NULL);
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t') || line[i + 1] == '\0')
		{
			str = (char*)malloc(sizeof(char) * (i - ancla + 1));
			if (!str)
			{
				return (NULL);
			}
			while(ancla < i)
			{
				str[aux] = line[ancla];
				ancla++;
				aux ++;
			}
			if (line[i + 1] == '\0')
			{
				str[aux] = line[ancla];
				aux++;
			}
			str[aux] = '\0';
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*get_word_before(char *line, int i)
{
	char *str;
	int ancla;
	int aux;

	i++;
	aux = 0;
	ancla = i;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t') || line[i + 1] == '\0')
		{
			i++;
			str = (char*)malloc(sizeof(char) * (ancla - i + 1));
			if (!str)
			{
				return (NULL);
			}
			while(ancla - 1 > i)
			{
				str[aux] = line[i];
				i++;
				aux ++;
			}
			if (line[ancla + 1] == '\0')
			{
				str[aux] = line[ancla];
				aux++;
			}
			str[aux] = '\0';
			return (str);
		}
		i--;
	}
	return (NULL);

}



void change_wildcards(char *word_before, char *word_after, char *line, int i)
{
	DIR *dir;
	struct dirent *ent;
	char *str;

	if (word_before[0] == '/')
		dir = opendir("/");
	else
		dir = opendir(".");
	str = NULL;
	// Si pones opendir("./NOMbredirectorio entra en el")
	if (dir == NULL)
	{
		printf("no se puede abrir directorio");
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (word_before)
		{
			if (hay_palabra_before(word_before, ent->d_name))
			{
				if (!str)
				{
					str = ft_strdup(ent->d_name);
					str = ft_strjoin(str, " ");
					printf("%s ", str);
				}
				else
				{
					str = ft_strjoin(str, ent->d_name);
					str = ft_strjoin(str, " ");
					printf("%s ", str);
				}
			}
		}
		//printf("%s ", ent->d_name);
		//ent->d_type
	}
}

// si dejo * es que esta mal y si no lo sustituyo
char 	*gestion_wildcards(char *line)
{
	int i;
	char *word_before;
	char *word_after;

	i = 0;
	while(line[i])
	{
		if (line[i] == '*')
		{
			word_after = get_word_after(line, i);
			word_before = get_word_before(line, i);
			printf("\nword before = %s\n", word_before);
			printf("word after = %s\n", word_after);
			change_wildcards(word_before, word_after, line, i);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_parser *parser;
	int num_palabras = 0;
	t_list	*env_lst;
	int i;
	int len;
	char *line;
	char *env_aux;
	t_list *list;
	i = 0;
	len = 0;

	set_env_list(&env_lst, env);
	//print_env_lst(env_lst);
	while (argv[1][len])
		len++;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	line = (char*)malloc(sizeof(char)*(len + 1));
	if (!line)
		return 0;
	sustituir_dollar("hola me llamo $USER y tuu $PWD $US\n", env_lst);
	printf("%s\n", line);
	gestion_wildcards("hola l*e de pedro p*   ");
	//env_aux = get_env_var("USER", env_lst);
	//printf("%s", env_aux);
	
}
/*
int main(int argc, char **argv, char **env)
{
	t_parser *parser;
	int num_palabras = 0;
	char **env_list;
	t_list	*env_lst;
	int i;
	int len;
	char *line;
	t_list *list;
	i = 0;
	len = 0;

	env_list = 
	if (argc < 0)
		return (1);
	set_env_list(&env_lst, env);
	//print_env_lst(env_lst);
	while (argv[1][len])
		len++;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	line = (char*)malloc(sizeof(char)*(len + 1));
	if (!line)
		return 0;
	while (argv[1][i])
	{
		line[i] = argv[1][i];
		i++;
	}
	line[i] = '\0';
	parser->line = line;
	if (check_sintaxis(line) == 0)
	{
		printf("No vale \n");
		return (0);
	}
	check_dollar(parser, env_lst);
	num_palabras = separar(parser);
	list = parser->lexer;
	while(list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	free(line);
	free(parser);
	return (0);

}*/