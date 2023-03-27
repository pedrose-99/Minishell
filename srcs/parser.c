//Estructura posible para el parser

typedef struct s_lexer
{
	char 	*cmd // Aqui se guarda el comando
	char 	*flags // Aqui se guardan las flags
	char 	*stdin // Aqui se guarda el stdin
	char 	*stdout // Aqui se guarda el stdou
	int 	operator; // Para identificar las redirecciones (tokens)
	bool	exito; // Para comprobar si ha funcionado o no
}				t_lexer;

typedef struct s_parser
{
	char 	*line; // Esta linea va a contener 
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


