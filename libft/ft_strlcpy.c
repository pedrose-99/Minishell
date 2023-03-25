/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/17 12:22:21 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	cont;
	char	*ptr_src;

	cont = 0;
	ptr_src = (char *)src;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (ptr_src[cont] && cont < (size - 1))
		{
			dest[cont] = ptr_src[cont];
			cont++;
		}
		dest[cont] = '\0';
	}
	return (ft_strlen(src));
}
