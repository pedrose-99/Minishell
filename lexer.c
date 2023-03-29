#include "libft/libft.h"
#include <stdio.h>

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
	t_list	**lista_comandos; // Para guardar cada comando en su lista
	t_list *lexer; // Esta seria la tabla que contiene todos los datos del lexer
	int 	num_comd; // Numero de comandos

}				t_parser;

void	init_parser(t_parser *parser)
{
	parser->line = "";
	parser->lista_comandos = NULL;
}

void	copiar_en_array(t_parser *parser, char **array_aux, int num_palabras, int i, int ancla)
{
	int aux;

	aux = 0;
	while(ancla < i)
	{
		array_aux[num_palabras - 1][aux] = parser->line[ancla];
		ancla++;
	}
	//añadir a la lista el array_aux[num_palabras]
	printf("%s", array_aux[0]);
}

// Esta funcion me guarda la palabra en un array temporal y me devuelve el nuevo ancla
int		condition_space(t_parser *parser, int ancla, int i, char **array_aux, int num_palabras)
{
	copiar_en_array(parser, array_aux, num_palabras, i, ancla);
	while(parser->line[i] == ' ' || parser->line[i] == '\t')
		i++;
	return i;
}

int condition_comillas(t_parser *parser, int i, char **array_aux, int num_palabras, char c)
{
	int ancla;
	
	ancla = i;
	while(parser->line[i] != c)
	{
		i++;
	}
	while(parser->line[i] != ' ' || parser->line[i] != '\t')
		i++;
	copiar_en_array(parser, array_aux, num_palabras, i, ancla);
	return (i);

}
// Esta funcion contara el numero de palabras que hay para separar
int		contar_palabras(t_parser *parser)
{
	int i;
	int ancla;
	char **array_aux;
	int num_palabras;

	i = 0;
	num_palabras = 0;
	while(parser->line[i] == ' ' || parser->line[i] == '\t')
		i++;
	ancla = i;
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
		else if(parser->line[i] == "'")
		{
			num_palabras++;
			ancla = condition_comillas(parser, i, array_aux, num_palabras, "'");
			i = ancla;
		}
		else if (parser->line[i] == '|' || parser->line[i] == '>' || parser->line[i] == '<')
		{
			num_palabras++;
			ancla++;
			array_aux[num_palabras][0] = parser->line[i];
		}
		else if (parser->line[i] == '$')
		{
			num_palabras++;
			//Hacer funcion pa hacer el $loquesea
		}
		i++;
	}
	return(num_palabras);
}


void	separar_linea(t_parser *parser)
{

}


int main(int argc, char **argv)
{
	t_parser *parser;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	parser->line = argv[1];
	printf("%s", parser->line);
	return (0);

}