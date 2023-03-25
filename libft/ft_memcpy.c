/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 20:54:36 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	char		*char_dest;
	const char	*char_src;
	size_t		c;

	char_dest = (char *)dest;
	char_src = (const char *)src;
	c = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (c < n)
	{
		char_dest[c] = char_src[c];
		c++;
	}	
	return (dest);
}
