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
	return(parentesis_cerrado - parentesis_abierto);
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
		if (line[i] == '(')
			i = condition_parentesis(line, i);
		else if (line[i] == 39)
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
		check_paren = check_parentesis(line);
	if (check_paren == 0)
		check_other_carac = check_caract(line);
	if (check_other_carac)
		return (1);
	return (0);
}

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