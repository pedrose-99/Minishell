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
	parser->line = (char *)malloc(sizeof(char *));
	parser->line = "";
	parser->lista_comandos = NULL;
}

void	copiar_en_array(t_parser *parser, char **array_aux, int num_palabras, int i, int ancla)
{
	int aux;
	array_aux[num_palabras -1] =(char *)malloc(sizeof(char*));
	aux = 0;
	while(ancla < i)
	{
		array_aux[num_palabras - 1][aux] = parser->line[ancla];
		aux++;
		ancla++;
	}
	array_aux[num_palabras - 1][aux] = '\0';
	//añadir a la lista el array_aux[num_palabras]
}

// Esta funcion me guarda la palabra en un array temporal y me devuelve el nuevo ancla
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
// Esta funcion contara el numero de palabras que hay para separar
int		contar_palabras(t_parser *parser)
{
	int i;
	int ancla;
	char **array_aux;
	int num_palabras;

	i = 0;
	num_palabras = 0;
	array_aux =(char **)malloc(sizeof(char**));
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
			printf("%c'\n'", parser->line[i]);
		}
		else if(parser->line[i] == 39)
		{
			num_palabras++;
			ancla = condition_comillas(parser, i, array_aux, num_palabras, 39);
			i = ancla;
		}
		else if (parser->line[i] == '|' || parser->line[i] == '>' || parser->line[i] == '<')
		{
			num_palabras++;
			array_aux[num_palabras -1] =(char *)malloc(sizeof(char*));
			ancla++;
			array_aux[num_palabras - 1][0] = parser->line[i];
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


int main(int argc, char **argv)
{
	t_parser *parser;
	int num_palabras = 0;
	int i;
	int len;
	char *line;
	
	i = 0;
	len = 0;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	line = (char*)malloc(sizeof(char*));
	while (argv[1][len])
		len++;
	line[i] = argv[1][0];
	i++;
	printf("%c", line[1]);
	while (i < len)
	{
		line[i] = argv[1][i];
		i++;
	}
	line[i] = '\0';
	parser->line = line;
	num_palabras = contar_palabras(parser);
	printf("%s", parser->line);
	printf("%d", num_palabras);
	return (0);

}