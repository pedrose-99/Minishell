/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/14 10:38:13 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cont;
	char	*substring;

	cont = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > (ft_strlen(s) - start))
		substring = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substring = malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	while (cont < len && s[start])
	{
		substring[cont] = s[start];
		cont++;
		start++;
	}
	substring[cont] = '\0';
	return (substring);
}
