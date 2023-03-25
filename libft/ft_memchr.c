/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 17:37:59 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *string, int c, unsigned int len)
{
	unsigned int	cont;
	unsigned char	*p;

	cont = 0;
	p = (unsigned char *)string;
	while (cont < len)
	{
		if (p[cont] == (unsigned char)c)
			return (&p[cont]);
		cont++;
	}
	return (0);
}
