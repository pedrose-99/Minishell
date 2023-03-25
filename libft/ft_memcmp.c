/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 17:38:09 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *string1, void *string2, unsigned int len)
{
	unsigned int	cont;
	unsigned char	*p1;
	unsigned char	*p2;

	cont = 0;
	p1 = string1;
	p2 = string2;
	while (cont < len)
	{
		if (p1[cont] == p2[cont])
			cont++;
		else if (p1[cont] != p2[cont])
			return (p1[cont] - p2[cont]);
	}
	return (0);
}
