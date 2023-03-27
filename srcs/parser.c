//Estructura posible para el parser
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_lexer
{
	char 	*cmd; // Aqui se guarda el comando
	char 	*flags; // Aqui se guardan las flags
	char 	*stdin; // Aqui se guarda el stdin
	char 	*stdout; // Aqui se guarda el stdou
	int 	operator; // Para identificar las redirecciones (tokens)
	int		exito; // Para comprobar si ha funcionado o no
}				t_lexer;

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
	t_list	**lista_comandos; // Para guardar cada comando en su lista
	t_lexer *lexer; // Esta seria la tabla que contiene todos los datos del lexer
	int 	num_comd; // Numero de comandos

}				t_parser;

// Para el arbol:

/* Tenemos el arbol binario con cada uno de los token

	int resultado_token;
	resultado_token = scantoken(token);

	if (resultado_token > otro_token)
		se ejecuta 1 el resultado_token;

Prueba
*/

t_lexer *init_lexer()
{
	t_lexer *lexer;

	lexer = (t_lexer*)malloc(sizeof(t_lexer));
	lexer->cmd = "";
	lexer->flags = "";
	lexer->stdin = "STDIN";
	lexer->stdout = "STDOUT";
	lexer->operator = 0;
	lexer->exito = 1;
	return lexer;
}

void	init_parser(t_parser *parser)
{
	parser->line = "";
	parser->lista_comandos = NULL;
	parser->lexer = init_lexer();
}

int check_num_parentesis(char *line, int start)
{
	int num_paren_abiert;
	int num_paren_cerra;

	num_paren_abiert = 0;
	num_paren_cerra = 0;
	while(line[start])
	{
		if (line[start] == '(')
			num_paren_abiert++;
		if (line[start] == ')')
			num_paren_cerra++;
		start++;
	}
	return(num_paren_cerra - num_paren_abiert);
}

int		pos_parentesis(line, i)
{
	int aux;
	int num_parent_abiert;
	
	num_paren_abiert = 0;
	i++;
	while(line[i])
	{
		if (line[i] == '(')
		{
			num_paren_abiert++;
			i++;
			while(num_paren_abiert != 0)
			{
				if (line[i] == '(')
					num_paren_abiert++;
				if (line[i] == ')')
					num_paren_abiert--;
				i++;
			}
		}
		if (line[i] == ')')
			return (i);
		i++;
	}
}

void	split_line(t_list **lst, char *line, int c)
{
	int		i;
	int		end_parentesis;

 	i = 0;
	end_parentesis = 0;
	while (line[i] && line[i] == ' ')
	i++;
	if (!check_num_parentesis(line, i))
		return ;
	if (line[i] == '(')
	{
		end_parentesis = pos_parentesis(line, i);
		
	}
}

int main(int argc, char **argv)
{
	t_parser *parser;
	parser = (t_parser*)malloc(sizeof(t_parser));
	init_parser(parser);
	parser->line = argv[1];
	lst_split(parser->lista_comandos, parser->line, '\0');
	free(parser->lexer);
	printf("%s", parser->line);
	return (0);

}