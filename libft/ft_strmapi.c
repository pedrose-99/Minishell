/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/09/27 12:04:18 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_len;
	int		cont;
	char	*string;

	s_len = ft_strlen(s);
	cont = 0;
	string = (char *)malloc(sizeof(char) * s_len + 1);
	if (string == NULL)
		return (NULL);
	while (s[cont] != '\0')
	{
		string[cont] = f(cont, s[cont]);
		cont++;
	}
	string[cont] = '\0';
	return (string);
}
