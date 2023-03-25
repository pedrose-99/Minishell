#include "libft.h"

char	*aux_join(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	free(s1);
	return (aux);
}