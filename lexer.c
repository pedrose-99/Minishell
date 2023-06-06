#include "libft/libft.h"
#include "includes/minishell.h"
#include <stdio.h>

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
	t_list *lexer; // Esta seria la tabla que contiene todos los datos del lexer // Numero de comandos
}				t_parser;

void funcion_wildcards_conbarra(char *ruta, char **line, int num_barras);



// SI *S* busca todas las palabras que contengan S
char	**make_array_wildcard(char *s)
{
	char	**array_2d;
	int		cont;
	int		len;

	cont = 0;
	len = 0;
	if (s[cont] == '*')
		len++;
	while (s[cont] == '*' && s[cont])
			cont++;
	while (s[cont])
	{
		len++;
		while (s[cont] != '*' && s[cont])
			cont++;
		while (s[cont] == '*' && '*' != 0)
			cont++;
	}
	cont--;
	if (s[cont] == '*')
		len++;
	array_2d = (char **)malloc(sizeof(char *) * (len + 1));
	return (array_2d);
}

static void	free_array2d(char **array_2d)
{
	int		i;

	i = 0;
	while (array_2d[i])
	{
		free(array_2d[i]);
		i++;
	}
	free(array_2d);
	array_2d = NULL;
}

int	guardar_asterisco_principio(char **array_2d, char const *s, int i)
{
	int	j;

	j = 0;
	if (s[i] == '*')
	{
		array_2d[j] = ft_substr(s, 0, 1);
		j++;
	}
	return (j);
}

void	guardar_asterisco_final(char **array_2d, char const *s, int i, int j)
{
	i--;
	if (s[i] == '*')
	{
		array_2d[j] = ft_substr("*", 0, 1);
		j++;
	}
	array_2d[j] = NULL;
}

int	incrementar_contador(char const *s, int i, int word_size)
{
	i = i + word_size;
	while (s[i] == '*' && s[i])
		i++;
	return (i);
}

static void	fill_array_wildcard(char **array_2d, char const *s)
{
	int		i;
	int		j;
	int		word_size;

	i = 0;
	j = guardar_asterisco_principio(array_2d, s, i);
	while (s[i] == '*' && s[i])
		i++;
	while (s[i])
	{
		word_size = 0;
		while (s[i + word_size] != '*' && s[i + word_size] != '\0')
			word_size++;
		array_2d[j] = ft_substr(s, i, word_size);
		if (!array_2d[j])
		{
			free_array2d(array_2d);
			break ;
		}
		j++;
		i = incrementar_contador(s, i, word_size);
	}
	guardar_asterisco_final(array_2d, s, i, j);
}

char **new_split(char *s)
{
	char	**array_2d;

	if (!s)
		return (NULL);
	array_2d = make_array_wildcard(s);
	if (!array_2d)
		return (NULL);
	fill_array_wildcard(array_2d, s);
	if (!array_2d)
		return (NULL);
	return (array_2d);
}

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] && s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strcpy(char *s1, char *s2)
{
	int	i;

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
	int	aux_abierto;
	int	aux_cerrado;

	aux_abierto = 1;
	aux_cerrado = 0;
	while (aux_abierto != aux_cerrado)
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
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int		condicion_parser_line(t_parser *parser, int ancla, int i)
{
	if (ancla != i)
		ft_lstadd_back(&parser->lexer,
			ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
	ancla = i;
	if (parser->line[i] == parser->line[i + 1])
	{
		ft_lstadd_back(&parser->lexer,
			ft_lstnew(ft_substr(parser->line, ancla, 2)));
		i++;
	}
	else
		ft_lstadd_back(&parser->lexer,
			ft_lstnew(ft_substr(parser->line, ancla, 1)));
	i++;
	i = saltar_espace(parser->line, i);
	return (i);
}

int 	condicion_parser_parent(t_parser *parser, int ancla, int i)
{
	if (ancla != i)
		ft_lstadd_back(&parser->lexer,
			ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
	ancla = i;
	i++;
	ancla = i;
	i = condition_parentesis(parser->line, i);
	ft_lstadd_back(&parser->lexer,
		ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
	i++;
	i = saltar_espace(parser->line, i);
	return (i);
}

int 	separar(t_parser *parser)
{
	int		i;
	int		ancla;
	int		parent;

	i = 0;
	ancla = 0;
	while (parser->line[i])
	{
		if (parser->line[i] == '|' || parser->line[i] == '>'
			|| parser->line[i] == '<' || parser->line[i] == '&')
		{
			i = condicion_parser_line(parser, ancla, i);
			ancla = i;
		}
		else if (parser->line[i] == '(')
		{
			i = condicion_parser_parent(parser, ancla, i);
			ancla = i--;
		}
		i++;
	}
	if (parser->line[i] != ')')
		ft_lstadd_back(&parser->lexer,
			ft_lstnew(ft_substr(parser->line, ancla, i - ancla)));
	return (0);
}


int condicion_check_parent(char *line, int i)
{
	if (line[i] == '"')
	{
		i++;
		while (line[i] != '"')
			i++;
	}
	else if (line[i] == 39)
	{
		i++;
		while (line[i] != 39)
			i++;
	}
	return (i);
}

int		check_parentesis(char *line)
{
	int		i;
	int		parentesis_abierto;
	int		parentesis_cerrado;

	i = 0;
	parentesis_abierto = 0;
	parentesis_cerrado = 0;
	while (line[i])
	{
		i = condicion_check_parent(line, i);
		if (line[i] == '(')
			parentesis_abierto++;
		if (line[i] == ')')
			parentesis_cerrado++;
		i++;
	}
	i = (parentesis_abierto - parentesis_cerrado);
	if (i == 0)
		return (1);
	else
		return (0);
}

int 	check_comillas(char *line)
{
	int		i;
	int		comillas_simples;
	int		comillas_dobles;

	i = 0;
	comillas_simples = 0;
	comillas_dobles = 0;
	while (line[i])
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

int condition_check_caract(char *line, int i, char c)
{
	while (line[i] != c)
		i++;
	return (i);
}

int check_caract(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			i++;
			i = condition_check_caract(line, i, 39);
		}
		else if (line[i] == '"')
		{
			i++;
			i = condition_check_caract(line, i, '"');
		}
		else if (line[i] == ',' || line[i] == ';' || line[i] == 92)
			return (0);
		i++;
	}
	return (1);
}

int		check_sintaxis(char *line)
{
	int		check_paren;
	int		check_other_carac;

	check_other_carac = 0;
	if (check_comillas (line))
		check_paren = check_parentesis(line);
	else
		return (0);
	if (check_paren == 1)
		check_other_carac = check_caract(line);
	else
		return (0);
	if (check_other_carac)
		return (1);
	else
		return (0);
}



char	**env_list_to_array(t_list *env_list)
{
	char	**env_array;
	char	*content;
	int		i;

	i = 0;
	env_array = (char**)ft_calloc((ft_lstsize(env_list) + 1), sizeof(char*));
	while (env_list)
	{
		content = (char *)env_list->content;
		env_array[i] = content;
		env_list = env_list->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char *condicion_get_word(char *str, char *line, int ancla, int i)
{
	int aux;

	aux = 0;
	str = (char *)malloc(sizeof(char) * (i - ancla + 1));
	if (!str)
		return (NULL);
	while (ancla < i)
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

char	*get_word(char *line, int i)
{
	char	*str;
	int		ancla;

	i++;
	ancla = i;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t') || line[i + 1] == '\0')
		{
			str = condicion_get_word(str, line, ancla, i);
			return (str);
		}
		i++;
	}
	return (NULL);
}


char *sustituir_dollar_new_word(char *line, int i, char *new_word, int len)
{
	char	*new_line1;
	char	*new_line2;

	new_line1 = ft_substr(line, 0, i);
	new_line1 = aux_join(new_line1, new_word);
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	if (line[i])
	{
		new_line2 = ft_substr(line, i, len - 1);
		new_line1 = aux_join(new_line1, new_line2);
	}
	line = ft_strdup(new_line1);
	return (line);

}
char *sustituir_dollar_not_new_word(char *line, int i, int len)
{
	char	*new_line1;
	char	*new_line2;

	new_line1 = ft_substr(line, 0, i);
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	if (line[i])
	{
		new_line2 = ft_substr(line, i, len - 1);
		new_line1 = aux_join(new_line1, new_line2);
	}
	line = ft_strdup(new_line1);
	return (line);
}

void	sustituir_dollar(char *line, t_list *env_list)
{
	int		i;
	char	*new_word;
	int		len;

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
				line = sustituir_dollar_new_word(line, i, new_word, len);
			else
				line = sustituir_dollar_not_new_word(line, i, len);
		}
		i++;
		new_word = NULL;
	}
	//printf("%s", line); //Quitar seguramente
}

int		hay_palabra_before(char *word_before, char *archivo)
{
	int		i;

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
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (archivo[size])
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
	char	*str;
	int		ancla;
	int		aux;

	aux = 0;
	ancla = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	if ((i - 1)== ancla)
		return (NULL);
	i--;
	str = (char *)malloc(sizeof(char) * (i - ancla + 1));
	if (!str)
		return (NULL);
	ancla++;
	while (ancla <= i)
	{
		str[aux] = line[ancla];
		ancla++;
		aux ++;
	}
	str[aux] = '\0';
	return (str);
}

char	*get_word_before(char *line, int i)
{
	char	*str;
	int		ancla;
	int		aux;

	aux = 0;
	ancla = i; 
	while (line[ancla] != ' ' && line[ancla] != '\t' && ancla != 0)
		ancla--;
	if (ancla != 0)
		ancla++;
	if (i == ancla)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (i - ancla + 1));
	if (!str)
		return (NULL);
	while (ancla < i)
	{
		str[aux] = line[ancla];
		ancla++;
		aux ++;
	}
	str[aux] = '\0';
	return (str);
}

int		check_size(char *word_before, char *word_after, char *name)
{
	int		size;
	int		size_word_a;
	int		size_word_b;

	size = 0;
	size_word_a = 0;
	size_word_b = 0;
	while (name[size])
		size++;
	while (word_before[size_word_b])
		size_word_b++;
	while (word_after[size_word_a])
		size_word_a++;
	if (size_word_b > size || size_word_a > size)
		return (0);
	else
	{
		size--;
		return (size);
	}
}

char *case_director_word_before(char *str, char *word_before, char *name)
{
	if (word_before)
	{
		if (word_before[0] == '/')
			str = aux_join("/", name);
		else
		{
			str = getcwd(str, 100);
			str = aux_join(str, "/");
			str = aux_join(str, name);
		}
		if (access(str, R_OK) != 0)
			return (NULL);
		return (str);
	}
	return (NULL);
}

int increment_size_case_director(char *word)
{
	int		i;

	i = 0;
	while (word[i])
		i++;
	i--;
	return (i);
}

int	condicion_case_director(char *word_after, char *name, int size, int j)
{
	while (word_after[j] && size >= 0)
	{
		if (word_after[j] != name[size])
			return (0);
		j--;
		size--;
	}
	return (1);
}

char *case_director(char *word_after, char *word_before, char *name, struct dirent *ent)
{
	int		j;
	int		size;
	char	*str;

	size = increment_size_case_director(name);
	j = increment_size_case_director(word_after);
	j--;
	str = case_director_word_before(str, word_before, name);
	if (ent->d_type == 4 || ent->d_type == 10)
	{
		if (condicion_case_director(word_after, name, size, j) == 0)
			return (NULL);
	}
	else
		return (NULL);
	if (name[0] == '.' && (name[1] == '.' || name[1] == '\0'))
		return (NULL);
	name = aux_join(name, "/");
	return (name);
}

char *check_malloc(char *str, int size)
{
	if (size == 0)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (2));
	if (!str)
		return (NULL);
	return (str);
}

char *guardar_barra(char *word_before, int *aux, int *i, struct dirent *ent)
{
	char	*str;

	*i = 0;
	*aux = 0;
	str = (char *) malloc(sizeof(char) * (2));
	if (!str)
		return (NULL);
	if (word_before[*aux] == '/')
	{
		(*aux)++;
		str[0] = '/';
	}
	while (word_before[*aux])
	{
		if (word_before[*aux] != ent->d_name[*i])
		{
			free(str);
			return (NULL);
		}
		(*i)++;
		(*aux)++;
	}
	return (str);
}

int	incrementar_case_bef_aft(char *word_after, int j)
{
	j = 0;
	while (word_after[j])
		j++;
	j--;
	return (j);
}

int condicion_word_after_size(char *word_after, int *j, struct dirent *ent, int *size)
{
	if (word_after[*j] != ent->d_name[*size])
		return (0);
	//*j--;
	//*size--;
	return (1);
}

//Arreglar
char *case_word_before_after(char *word_before, char *word_after,
	struct dirent *ent, char *str)
{
	int		i;
	int		j;
	int		size;
	int		aux;

	size = check_size(word_before, word_after, ent->d_name);
	if (size == 0)
		return (NULL);
	str = guardar_barra(word_before, &aux, &i, ent);
	if (!str)
		return (NULL);
	j = incrementar_case_bef_aft(word_after, j);
	if (word_after[j] == '/')
	{
		str = aux_join(str,
				case_director(word_after, word_before, ent->d_name, ent));
		if (ent->d_name[i] == '.')
			return (NULL);
		return (str);
	}
	while (word_after[j] && size >= i)
	{
		if (word_after[j] != ent->d_name[size])
			return (0);
		j--;
		size--;
	}
	if (ent->d_name[i] == '.')
		return (NULL);
	str = aux_join(str, ent->d_name);
	return (str); //CASO SRCS*S
}

int condicion_case_word_before(char *word_before, int aux, char *str)
{
	if (word_before[aux] == '/')
	{
		aux++;
		str[0] = '/';
	}
	return (aux);
}

char *case_word_before(char *word_before, char *name, struct dirent *ent)
{
	int		i;
	int		aux;
	char	*str;
	int		ancla;

	i = 0;
	aux = 0;
	str = (char *)malloc(sizeof(char) * (2));
	if (!str)
		return (NULL);
	aux = condicion_case_word_before(word_before, aux, str);
	while (word_before[aux])
	{
		if (word_before[aux] != name[i])
		{	
			free(str);
			return (NULL);
		}
		i++;
		aux++;
	}
	if (name[i] == '.' || (name[0] == '.' && name[1] == '\0'))
		return (NULL);
	str = aux_join(str, name);
	return (name);
}

char *condicion_case_word_after(char *name, char *word_after, int j,
	struct dirent *ent)
{
	name = case_director(word_after, NULL, name, ent);
	if (name)
	{
		if (name[0] == '.')
			return (NULL);
	}
	return (name);
}

char *case_word_after(char *word_after, char *name, struct dirent *ent)
{
	int		j;
	int		size;

	size = increment_size_case_director(name);
	j = increment_size_case_director(word_after);
	if (word_after[j] == '/')
		return (condicion_case_word_after(name, word_after, j, ent));
	while (word_after[j] && size >= 0)
	{
		if (word_after[j] != name[size])
		{
			//free(name);
			return (NULL);
		}
		j--;
		size--;
	}
	if (name[0] == '.' && (name[1] == '.' || name[1] == '\0'))
		return (NULL);
	return (name);
}

int	check_num_asteriscos(char *str, int i)
{
	int		num_ast;
	int		aux;

	aux = i;
	num_ast = 0;
	while (str[aux] != ' ' && str[aux] != '\t' && str[aux] != '\0')
	{
		if (str[aux] == '*')
			num_ast++;
		aux++;
	}
	return (num_ast);
}

void change_wildcards(char *word_before, char *word_after, char *line, int i)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*str;

	if (!word_before || word_before[0] != '/')
		dir = opendir(".");
	else
		dir = opendir("/");
	if (dir == NULL)
		return ;
	while ((ent = readdir(dir)) != NULL)
	{
		if (word_before && word_after)
			str = case_word_before_after(word_before, word_after, ent, str);
		else if (word_before)
			str = case_word_before(word_before, ent->d_name, ent);
		else if (word_after)
			str = case_word_after(word_after, ent->d_name, ent);
		if (str)
			printf("%s ", str);
	}
	printf("\n");
}

char	*get_word_after_m(char *line, int i)
{
	char	*str;
	int		ancla;
	int		aux;

	aux = 0;
	ancla = i;
	i++;
	while (line[i] != ' ' && line[i] != '\t'
		&& line[i] != '\0' && line[i] != '*')
		i++;
	if ((i - 1)== ancla)
		return (NULL);
	i--;
	str = (char *)malloc(sizeof(char) * (i - ancla + 1));
	if (!str)
		return (NULL);
	ancla++;
	while (ancla <= i)
	{
		str[aux] = line[ancla];
		ancla++;
		aux ++;
	}
	str[aux] = '\0';
	return (str);
}

int ft_strlen_matriz(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}
char *get_name(char *ruta, struct dirent *ent)
{
	char	*nombrecompleto;
	int		tmp;

	tmp = ft_strlen(ruta);
	nombrecompleto = malloc(tmp + ft_strlen(ent->d_name) + 2);
	if (ruta[tmp - 1] == '/')
		nombrecompleto = aux_join(ruta, ent->d_name);
	else if (ruta[0] == '.')
		nombrecompleto = ft_strdup(ent->d_name);
	else
	{
		nombrecompleto = aux_join(ruta, "/");
		nombrecompleto = aux_join(nombrecompleto, ent->d_name);
	}
	return (nombrecompleto);
}
int	aparece_al_principio(char *ruta, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[0] == '*')
		return (1);
	while (line[j] && ruta[i])
	{
		if (ruta[i] == line[j])
		{
			i++;
			j++;
		}
		else
			return (0);
	}
	return (1);
}

int		incrementar_aparece_en_medio(char *line)
{
	int	i;

	while (line[i])
		i++;
	return (i);
}

int		avanzar_aparece_en_medio(char *line)
{
	int	j;

	j = 0;
	while (line[j] != '/')
		j++;
	j--;
	return (j);
}

int aparece_en_medio_barra(struct dirent *ent, char *line)
{
	int	i;
	int	j;
	int	ancla;

	i = incrementar_aparece_en_medio(ent->d_name);
	j = avanzar_aparece_en_medio(line);
	ancla = j;
	while (line[j] && ent->d_name[i])
	{
		if (line[j] == ent->d_name[i++])
			j++;
		else
		{
			j = ancla;
			if (line[j] == ent->d_name[i])
			{
				i++;
				j++;
			}
		}
		if (line[j] == '/')
			return (1);
	}
	return (0);
}

int aparece_en_medio(struct dirent *ent, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[j])
	{
		if (line[j++] == '/')
			return (aparece_en_medio_barra(ent, line));
	}
	j = 0;
	while (line[j] && ent->d_name[i])
	{
		if (line[j++] == ent->d_name[i++])
		{
			if (line[j] == '\0')
				return (1);
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (0);
}

int	hay_barra(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
int incrementar_hay_algo_enmedio(char *line, char *ruta, int *i, int cont)
{
	while (line[*i] == ruta[cont] && line[*i] && ruta[cont])
	{
		cont++;
		(*i)++;
	}
	return (cont);
}
int		funcion_hay_algo_enmedio(char *ruta, char *line, int cont)
{
	int		i;
	int		ancla;

	i = 0;
	while (ruta[cont] && line[i])
	{
		if (ruta[cont] != line[i])
			cont++;
		else
		{
			ancla = cont + 1;
			cont = incrementar_hay_algo_enmedio(line, ruta, &i, cont);
			if (line[i] != '\0' && ruta[cont] != '\0')
			{
				i = 0;
				cont = ancla;
			}
			else if (ruta[cont] == '\0' && line[i] != '\0')
				return (0);
			else if (ruta[cont] != '\0' && line[i] == '\0')
				return (cont);
			return (-1);
		}
	}
	return (0);
}

int		aparece_al_final(char *ruta, char *line, int ancla, struct dirent *ent)
{
	int		i;
	int		j;

	i = increment_size_case_director(ruta);
	j = increment_size_case_director(line);
	if (line[j] == '/')
		return (-1);
	while (j >= 0)
	{
		if (ruta[i] == line[j])
		{
			i--;
			j--;
		}
		else
			return (0);
	}
	i++;
	if (ancla > i)
		return (0);
	return (1);
}

//Arreglar
void	funcion_wildcards_sinbarra(char *ruta, char **line, int pos)// añadir t_list **list
{
	DIR		*dir;
	struct	dirent *ent;
	char	*nombrecompleto;
	int		cont;
	int		i;

	cont = 0;
	i = 0;
	dir = opendir(ruta);
	if (dir == NULL)
		return ;
	ent = readdir (dir);
	while (ent != NULL)
	{
		cont = 0;
		if ((ft_strcmp(ent->d_name, ".") != 0)
			&& (ft_strcmp(ent->d_name, "..") != 0))
		{
			if (aparece_al_principio(ent->d_name, line[0]) == 1)
			{
				pos++;
				if (line[0][0] != '*')
				{
					while (line[0][cont])
						cont++;
				}
				while (pos != (ft_strlen_matriz(line) - 1) && cont != -42)
				{
					cont = funcion_hay_algo_enmedio(ent->d_name,
							line[pos], cont);
					pos++;
					if (cont == -1)
					{
						if (pos == (ft_strlen_matriz(line) - 1))
						{
							if (line[pos][0] == '*')
							{
								printf("%s\n", ent->d_name);
								cont = -42;
							}
							else
							{
								cont = -42;
							}
						}
					}
					if (cont == 0)
					{
						cont = -42;
					}
				}
				if (cont != -42)
				{
					if (line[pos][0] == '*')
					{
						printf("%s\n", ent->d_name);
					}
					else
					{
						if (aparece_al_final(ent->d_name,
								line[pos], cont, ent) == 1)
						{
							printf("\n%s\n", ent->d_name);
						}
						else if (aparece_al_final(ent->d_name,
								line[pos], cont, ent) == -1)
						{
							printf("%s\n", ruta);
						}
					}
				}
			}
		}
		ent = readdir (dir);
		pos = 0;
	}
}

//Arreglar
void	funcion_wildcards_sinbarra_dps(char *ruta, char **line, int pos)// añadir t_list **list
{
	DIR				*dir;
	struct dirent	*ent;
	char			*nombrecompleto;
	int				cont;
	int				i;

	cont = 0;
	i = 0;
	dir = opendir(ruta);
	if (dir == NULL)
	{
		return ;
	}
	ent = readdir (dir);
	while (ent != NULL)
	{
		cont = 0;
		if ((ft_strcmp(ent->d_name, ".") != 0)
			&& (ft_strcmp(ent->d_name, "..") != 0))
		{
			nombrecompleto = get_name(ruta, ent);
			if (aparece_al_principio(nombrecompleto, line[0]) == 1)
			{
				pos++;
				if (line[0][0] != '*')
				{
					while (line[0][cont])
						cont++;
				}
				while (pos != (ft_strlen_matriz(line) - 1) && cont != -42)
				{
					cont = funcion_hay_algo_enmedio(nombrecompleto,
							line[pos], cont);
					pos++;
					if (cont == -1)
					{
						if (pos == (ft_strlen_matriz(line) - 1))
						{
							if (line[pos][0] == '*')
							{
								//printf("%s\n", ent->d_name);
								cont = -42;
							}
							else
								cont = -42;
						}
					}
					if (cont == 0)
						cont = -42;
				}
				if (cont != -42)
				{
					if (line[pos][0] == '*')
						printf("%s\n", nombrecompleto);
					else
					{
						if (aparece_al_final(nombrecompleto, line[pos],
								cont, ent) == 1)
							printf("Si cumple las condiciones: \n%s\n", nombrecompleto);
						else if (aparece_al_final(ent->d_name,
								line[pos], cont, ent) == -1)
						{
							ruta = aux_join(ruta, "/");
							printf("%s\n", ruta);
							return ;
						}
					}
				}
			}
		}
		ent = readdir (dir);
		pos = 0;
	}
}

char *funcion_num_barras_mayor(char *ruta, char **line, struct dirent *ent, int num_barras)
{
	char	*nombrecompleto;

	if (ent->d_type == 4)
	{
		nombrecompleto = get_name(ruta, ent);
		funcion_wildcards_conbarra(nombrecompleto, line, num_barras - 1);
	}
	return (nombrecompleto);
}

void	funcion_wildcards_conbarra(char *ruta, char **line, int num_barras)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*nombrecompleto;

	dir = opendir(ruta);
	if (dir == NULL)
		return ;
	ent = readdir (dir);
	while (ent != NULL)
	{
		if ((ft_strcmp(ent->d_name, ".") != 0)
			&& (ft_strcmp(ent->d_name, "..") != 0))
		{
			if (num_barras > 0)
				nombrecompleto = funcion_num_barras_mayor(ruta,
						line, ent, num_barras);
			else
			{
				funcion_wildcards_sinbarra_dps(ruta, line, 0);
				return ;
			}
		}
		ent = readdir (dir);
	}
}
int	cont_barras(char *line, int i)
{
	int		barras;

	barras = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '/')
			barras++;
		i++;
	}
	return (barras);
}

//Arreglar
char 	*gestion_wildcards(char *line)
{
	int		i;
	int		ancla;
	char	*word_before;
	char	*word_after;
	char	**aster;

	i = 0;
	while (line[i])
	{
		if (line[i] == '*')
		{
			if (check_num_asteriscos(line, i) == 1)
			{
				word_after = get_word_after(line, i);
				word_before = get_word_before(line, i);
				change_wildcards(word_before, word_after, line, i);
				free(word_before);
				free(word_after);
			}
			else
			{
				while (i > 0 && line[i] != ' ')
					i--;
				ancla = i;
				while (line[i] != ' ' && line[i])
					i++;
				aster = new_split(ft_substr(line, ancla, i));
				if (cont_barras(line, ancla) == 0)
				{
					if (aster[0][0] == '/')
						funcion_wildcards_sinbarra("/", aster, 0);
					else
					{
						funcion_wildcards_sinbarra(".", aster, 0);
					}
				}
				else
				{
					if (aster[0][0] == '/')
					{
						funcion_wildcards_conbarra("/", aster,
							cont_barras(line, ancla));
					}
					else
					{
						funcion_wildcards_conbarra(".", aster,
							cont_barras(line, ancla));
					}
				}
				free_array2d(aster);
			}
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
	if (argc == 1)
		return (0);
	set_env_list(&env_lst, env);
	//print_env_lst(env_lst);
	while (argv[1][len])
		len++;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	line = (char*)malloc(sizeof(char)*(len + 1));
	if (!line)
		return 0;
	// Mirar el $?
	//sustituir_dollar("hola me llamo $USER $PWD y tuu $US ps $USER", env_lst); FUNCIONA
	//printf("%s\n", line);
	gestion_wildcards("*s hahahsg"); ///
	system("leaks -q a.out");
	//gestion_wildcards("s*r*/* hahahsg");
	//funcion_wildcards("srcs/jjjd", "hola", 0);
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
}
			if (hay_palabra_before(word_before, ent->d_name))
			{
				if (!str)
				{
					str = ft_strdup(ent->d_name);
					str = aux_join(str, " ");
					printf("%s ", str);
				}
				else
				{
					str = aux_join(str, ent->d_name);
					str = aux_join(str, " ");
					printf("%s ", str);
				}*/
/*			if (pos == 0)
			{
				if (aparece_al_principio(ent, line[0]) == 1)
				{
					printf("Primera fase superada: %s\n", ent->d_name);
					pos++;
					if (pos != (ft_strlen_matriz(line) - 1))
					{
						if (hay_barra(line[pos]) && barra == 0)
						{
							//conseguir nombre completo.
							nombrecompleto = get_name(ruta, ent);
							// llamar a la funcion de nuevo con otra ruta y el contador a 1?
							funcion_wildcards(nombrecompleto, line, pos, 0);
							//barra = 1
							barra = 1;
						}
						else if (barra == 1)
						{
							aparece_en_medio_barra(ent, line[pos]);
							//Hacer aparece_en_medio_barra()
							//si se cumple condicion hacer recursividad obteniendo su nueva ruta y entrando en ella aumentando pos++;
							//Si no se cumple seguir con el siguiente caso
						}
						else
						{
							//Posible while (pos != ft_strlen_matriz - 1)
							//Comrpobar si no hay barra. 
							//PROBLEMA: ¿pasar ruta desde la posicion actual del ent->d_name? problema luego al comprobar todo
						}
						solucion = aparece_en_medio(ent, line[pos]);
						printf("Aparece en medio: %d y es %s\n", solucion, ent->d_name);
					}
				if (ent->d_type == 4)
				{
					nombrecompleto = get_name(ruta, ent);
					funcion_wildcards(nombrecompleto, line, pos, 0);
				}
void	funcion_wildcards(char *ruta, char **line, int pos, int barra)// añadir t_list **list
{
	DIR *dir;
	struct dirent *ent;
	char *nombrecompleto;
	int cont;
	cont = 0;
	dir = opendir(ruta);
	if (dir == NULL)
	{
		printf("Por aqui no paso");
		return ;
	}
	printf("%s\n\n", ruta);
	while ((ent = readdir (dir)) != NULL)
	{
		if ((ft_strcmp(ent->d_name, ".") != 0) && (ft_strcmp(ent->d_name, "..") != 0))
		{
			//Posible while (pos != ft_strlen_matriz - 1)
			if (aparece_al_principio(ent, line[0]) == 1)
			{
				printf("Primera fase superada: %s\n", ent->d_name);
				pos++;
				if (pos != (ft_strlen_matriz(line) - 1))
				{
					else
					{
						//Posible while (pos != ft_strlen_matriz - 1)
						//Comrpobar si no hay barra. 
						//PROBLEMA: ¿pasar ruta desde la posicion actual del ent->d_name? problema luego al comprobar todo
					}
					solucion = aparece_en_medio(ent, line[pos]);
					printf("Aparece en medio: %d y es %s\n", solucion, ent->d_name);
				}
				if (ent->d_type == 4)
				{
					nombrecompleto = get_name(ruta, ent);
					funcion_wildcards(nombrecompleto, line, pos, 0);
				}
			}
			pos = ancla;
			}
			nombrecompleto = get_name(ruta, ent);
			if (ent->d_type != 4)
			{
		
				//funcion_wildcards(nombrecompleto, &line[pos], list);
			//si se cumple que existe:
			//ft_list_add(list, new_nodo(nombrecompleto))
		}
	}
}
			}*/