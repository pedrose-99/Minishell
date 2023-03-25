/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 19:44:44 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*char_dest;
	const char	*char_src;
	size_t		cont;

	char_dest = (char *)dest;
	char_src = (char *)src;
	cont = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (char_dest > char_src)
	{
		while (len-- > 0)
			char_dest[len] = char_src[len];
	}
	else
	{
		while (cont < len)
		{
			char_dest[cont] = char_src[cont];
			cont++;
		}
	}
	return (dest);
}
