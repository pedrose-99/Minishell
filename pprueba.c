#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


char *get_full_name(char *ruta, struct dirent *ent)
{
	char *nombrecompleto;
	int tmp;

	tmp=strlen(ruta);
	nombrecompleto=malloc(tmp+strlen(ent->d_name)+2);
	if (ruta[tmp-1]=='/')
	sprintf(nombrecompleto,"%s%s", ruta, ent->d_name);
	else
	sprintf(nombrecompleto,"%s/%s", ruta, ent->d_name);
 
	return nombrecompleto;
}

char *genera_pos_str(int niv)
{
	int i;
	char *tmp=malloc(niv*2+1);
	for (i=0; i<niv*2; ++i)
		tmp[i]=' ';
	tmp[niv*2]='\0';
	return tmp;
}


//Modificar para que en vez de i  sea numero de astericos
// empiezas a contar desde el ultimo siendo el ultimo == 0; si hay 3 astericos el 1 sera 3;
char	*get_word_after(char *line, int i)
{
	char *str;
	int ancla;
	int aux;

	aux = 0;
	ancla = i;
	i++;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0' && line[i] != '*')
		i++;
	if ((i - 1)== ancla)
		return (NULL);
	i--;
	str = (char*)malloc(sizeof(char) * (i - ancla + 1));
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

void	funcion_direct(char *ruta, int niv, int num_ast, char *line)
{
	DIR *dir;
	struct dirent *ent;
	char *nombre_comp;
	char *posstr;
	char *word_after;

	dir = opendir (ruta);
	num_ast--;
	if (dir == NULL)
	{
		printf("No es directorio");
		return ;
	}
	while ((ent = readdir(dir) != NULL))
	{
		if (num_ast == 0)
		{
			printf("%s", ruta);
		}
		else
		{
			word_after = get_word_after(line, num_ast);
			if (word_after[0] == '/')
			{
				nombre_comp = get_full_name(ruta, ent);
				//comparar word_after con la  el nombre completo
				// Si el orden es correcto y eso sigue pa alante.
				// si no hacer un return (0);
			}
		}
	}

	
}




unsigned cuenta_archivos(char *ruta, int niv)
{
	DIR *dir;
	struct dirent *ent;
	unsigned numfiles=0; 
	char *nombrecompleto;
	char *posstr;

	dir = opendir (ruta);
	if (dir == NULL)
	{
		printf("Vacio el directorio");
		return (0);
	}
	while ((ent = readdir (dir)) != NULL)
	{
		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
		{
			nombrecompleto=get_full_name(ruta, ent);
			if (ent->d_type!= 4)
			{
				++numfiles;
			}
			else
			{
				posstr=genera_pos_str(niv);
				printf("%sEntrando en: %s\n", posstr, nombrecompleto);
				printf("%s%s . Total: %u archivos ", posstr, nombrecompleto, cuenta_archivos(nombrecompleto, niv+1));
				printf("\n");
				free(posstr);
			}
			free(nombrecompleto);
		}
    }
	closedir (dir);
	return numfiles;
}



int main(int argc, char *argv[])
{
	unsigned num;

	if (argc != 2)
	{
		printf("Necesito el directorio\n");
		return (0);
	}
	printf("Entrando en: %s\n", argv[1]);
	num=cuenta_archivos(argv[1], 1);
	printf("%s . Total: %u archivos\n", argv[1], num);

	return EXIT_SUCCESS;
}