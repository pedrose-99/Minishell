#include "../libft/libft.h"

typedef struct s_nodo
{
	char cadena[1000];
	struct s_nodo *izquierda;
	struct s_nodo *derecha;
} 				t_nodo;

// Esta funcion genera un nuevo nodo
t_nodo *nuevo_nodo(char cadena[1000])
{
	t_nodo *nodo = (t_nodo*)malloc(sizeof(t_nodo));
	strcpy(nodo->cadena, cadena);
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	return (nodo);
}

// Esta funcion agrega una cadena ya sea al nodo derecho o al izquierdo 
void agregar(t_nodo *nodo, char *cadena)
{
	if (strcmp(cadena, nodo->cadena) > 0)
	{
		if (nodo->derecha == NULL)
			nodo->derecha = nuevo_nodo(cadena);
		else
			agregar(nodo->derecha, cadena);
	}
	else
	{
		if (nodo->izquierda == NULL)
			nodo->izquierda = nuevo_nodo(cadena);
		else
			agregar(nodo->izquierda, cadena);
	}
}

// Esta funcion busca una cadena en el arbol binario
t_nodo *buscar(t_nodo *nodo, char *cadena)
{
	if (nodo == NULL)
		return (NULL);
	if ((strcmp(cadena, nodo->cadena) == 0))
		return (nodo);
	else if (strcmp(cadena, nodo->cadena) > 0)
		return (buscar(nodo->derecha, cadena));
	else
		return (buscar(nodo->izquierda, cadena));
}

// Esta funcion primero pinta el nodo actual luego el izquierdo y luego el derecho
void print_arbol(t_nodo *nodo)
{
	if (nodo != NULL)
	{
		printf("%s,", nodo->cadena);
		print_arbol(nodo->izquierda);
		print_arbol(nodo->derecha);
	}
}

//Main de prueba probando a agregar cadenas
int main()
{
	t_nodo *raiz = NULL;

	if(raiz == NULL)
		raiz = nuevo_nodo("Nombre:");
	agregar(raiz, "Hola");
    agregar(raiz, "ME");
    agregar(raiz, "LLamo");
    agregar(raiz, "Pedro");
    agregar(raiz, "Como");
    agregar(raiz, "Te");
    agregar(raiz, "LLamas");
    agregar(raiz, "tu?");
    printf("\nPintar el arbol: \n");
	print_arbol(raiz);
	// Buscamos una palabra que no este
	char busqueda[1000] = "Patata";
    t_nodo*apuntador = buscar(raiz, busqueda);
    if (apuntador == NULL)
    {
        printf("%s no existe en el árbol\n", busqueda);
    }
    else
    {
        printf("%s sí existe en el árbol\n", busqueda);
    }
    // Otra búsqueda con algo que sabemos que sí existe
    char otra_busqueda[1000] = "Pedro";
    apuntador = buscar(raiz, otra_busqueda);
    if (apuntador != NULL)
    {
        printf("%s sí existe en el árbol\n", otra_busqueda);
    }
    else
    {
        printf("%s sí existe en el árbol\n", otra_busqueda);
    }
    return 0;
	return (0);
}