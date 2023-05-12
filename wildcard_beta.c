int fileMatch(char *str, char *query) 
{
    int i;
	int j;

	i = 0;
    j = 0;

    if ((!str && !query && !str[0]) || !query[0])
        return 0;
    while (query[i]) {
        if (!str[j])
            return 0;
        else if (query[i] == '*')
            while (query[i] && query[i] == '*') // I assume one * es lo mismo que poner varios seguidos. check...
                i++;
            while (str[j]) {
                j++;
                if (!str[j])
                    return 0;
                if (str[j] == query[i]) {
                    if (fileMatch(str[j + 1], query[i + 1]))
                        return 1;
                }
                return 0;
            }
        if (query[i] == str[j]) {
            j++;
            i++;
        }
    }
}

void findElement(char *query) 
{ //Checks current directory for a match; handles deh * checks
    int filesIndex;
    int nameIndex;


    filesIndex = 0;
    nameIndex = 0;
    foundFiles = NULL
    files = funcion_para_coger_el_listado_de_files()
    if (files == NULL)
        return NULL
    while (files[filesIndex]) {
        if (fileMatch(files[filesIndex], query))
            lst_add(strcpy(files[filesIndex])); //la string original se borra al acabar la función...
        filesIndex++;
    }
    return foundFiles;
}

void getFiles(char *query, previous_path, t_list **results) {
    int barLocation;
    char *next_path;
    char *current_level_folder;
    char *nextQuery;

    if (query == NULL)
        return
    if (query[0] == '/') {
        previous_path = 'home/$USER/' // <- Tiene que estar malloqueado; Rellenar con variable de entorno
        //quitar la / al principio de la query
    }

    barLocation = strchr(query, '/');
    if (barLocation != -1) { //No tengo ninguna barra en el path por lo que tengo que buscar aquí el archivo
        elements = findElement(previous_path, query, results);
        for (element in elements)
            //Añadir a results previous path + element;
            //Por cada elemento, añadir a results
    }
    else { // Tengo una barra en el path, por lo que voy a tener que meterme en un archivo.
        current_level_folder = substr(query, 0, barLocation);
        elements = findElement()
            //Por cada elemento, ejecutar
        for (element in elements) { // Si no se encuentra un elemento devuelve un array vacío, por lo que no entraría en el for
            if (previous_path == NULL)
                next_path = current_level_folder; 
            else {
                next_path = strjoin(previous_path, current_level_folder);
                free(previous_path)
            }
            free(current_level_folder);
            //función para cambiar el directorio a nextPath; 
            nextQuery = substr(query, barLocation, strlen(query - barLocation));
            free(query)
            getFiles(next_query, next_path, results)
            //Resetar el path al path previo; Probablemente mejor meterlo en una duper función que llame a la recursiva y resetee variables y esas mierdas una sola vez
        }
        free(elements);
        free(query);
        if (previous_path)
            free(previous_path);
    }
}