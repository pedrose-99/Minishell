/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/19 09:28:05 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dst_len;
	size_t	cont;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	dst_len = ft_strlen(dst);
	cont = 0;
	while (src[cont] != '\0' && dst_len + 1 < size)
	{
		dst[dst_len] = src[cont];
		dst_len++;
		cont++;
	}
	dst[dst_len] = '\0';
	return (dst_len + ft_strlen(&src[cont]));
}
