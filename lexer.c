#include "libft/libft.h"
#include <stdio.h>

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
	t_list *lexer; // Esta seria la tabla que contiene todos los datos del lexer // Numero de comandos

}				t_parser;

void	init_parser(t_parser *parser)
{
	parser->line = (char *)malloc(sizeof(char ));
	parser->line = "";
}

// Esta funcion me guarda la palabra en un array temporal y me devuelve el nuevo ancla
/*
int		condition_space(t_parser *parser, int ancla, int i, char **array_aux, int num_palabras)
{
	copiar_en_array(parser, array_aux, num_palabras, i, ancla);
	while(parser->line[i] == ' ' || parser->line[i] == '\t')
		i++;
	return i;
}

// Esta funcion te guarda todo lo que hay entre las
int condition_comillas(t_parser *parser, int i, char **array_aux, int num_palabras, char c)
{
	int ancla;
	int aux;
	
	ancla = i;
	i++;
	while(parser->line[i] != c)
	{
		i++;
	}
	while(parser->line[i] != ' ' && parser->line[i] != '\t')
		i++;
	copiar_en_array(parser, array_aux, num_palabras, i, ancla);
	return (i);

}
*/
/*
char**	copiar_en_array(t_parser *parser, char **array_aux, int num_palabras, int i, int ancla)
{
	int aux;

	aux = 0;
	aux = i - ancla;
	printf("Numero de letras del array: %d\n", aux);
	array_aux[num_palabras -1] =(char *)malloc(sizeof(char)*aux + 1);
	aux = 0;
	while(ancla <= i)
	{
		array_aux[num_palabras - 1][aux] = parser->line[ancla];
		aux++;
		ancla++;
	}
	array_aux[num_palabras - 1][aux] = '\0';
	printf("AQUI HACE LLA COPIA Y La IMPRIMIMOS: %s\n", array_aux[num_palabras - 1]);
	return (array_aux);
	//añadir a la lista el array_aux[num_palabras]
}
*/
int condition_parentesis(t_parser *parser, int i)
{
	int aux_abierto;
	int aux_cerrado;

	aux_abierto = 1;
	aux_cerrado = 0;
	while(aux_abierto != aux_cerrado)
	{
		if (parser->line[i] == '(')
			aux_abierto++;
		if (parser->line[i] == ')')
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
			i++;
			ancla = i;
			i = condition_parentesis(parser, i);
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
/*
// Esta funcion contara el numero de palabras que hay para separar
int		contar_palabras(t_parser *parser)
{
	int i;
	int ancla;
	char **array_aux;
	int num_palabras;

	i = 0;
	array_aux =(char **)malloc(sizeof(char**));
	while(parser->line[i] == ' ' || parser->line[i] == '\t')
		i++;
	ancla = i;
	num_palabras = 1;
	while(parser->line[i])
	{
		if (parser->line[i] == ' ' || parser->line[i] == '\t')
		{
			num_palabras++;
			ancla = condition_space(parser, ancla, i, array_aux, num_palabras);
		}
		else if(parser->line[i] == '"')
		{
			num_palabras++;
			ancla = condition_comillas(parser, i, array_aux, num_palabras, '"');
			i = ancla;
		}
		else if(parser->line[i] == 39)
		{
			num_palabras++;
			ancla = condition_comillas(parser, i, array_aux, num_palabras, 39);
			i = ancla;
		}
		else if (parser->line[i] == '|' || parser->line[i] == '>' || parser->line[i] == '<' || parser->line[i] == '&') //añadir ||   y &&
		{
			num_palabras++;
			if (parser->line[i + 1] == '|')
			{
				array_aux[num_palabras -1] =(char *)malloc(sizeof(char*));
				array_aux[num_palabras - 1][0] = parser->line[i];
				i++;
				array_aux[num_palabras - 1][0] = parser->line[i];
				ancla++;
			}
			array_aux[num_palabras -1] =(char *)malloc(sizeof(char*));
			array_aux[num_palabras - 1][0] = parser->line[i];
			i++;
			while(parser->line[i] == ' ' || parser->line[i] == '\t')
				i++;
			ancla = i;
		}
		else if (parser->line[i] == '$')
		{
			num_palabras++;
			//Hacer funcion pa hacer el $loquesea
		}
		else if(parser->line[i] == '(')
		{
			num_palabras++;
			ancla = condition_parentesis(parser, i, array_aux, num_palabras);
			i = ancla;
		}
		i++;
	}
	return(num_palabras);
}

*/

int main(int argc, char **argv)
{
	t_parser *parser;
	int num_palabras = 0;
	int i;
	int len;
	char *line;
	t_list *list;
	
	i = 0;
	len = 0;
	while (argv[1][len])
		len++;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	line = (char*)malloc(sizeof(char)*len + 1);
	while (i <= len)
	{
		line[i] = argv[1][i];
		i++;
	}
	line[i] = '\0';
	parser->line = line;
	num_palabras = separar(parser);
	list = parser->lexer;
	while(list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	free(line);
	return (0);

}