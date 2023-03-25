/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/01 17:24:04 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	cont;
	char	*array;

	if (size * count < count && (size * count) < size)
		return (NULL);
	array = malloc(size * count);
	cont = 0;
	if (!array)
		return (NULL);
	while (cont < (count * size))
	{
		array[cont] = 0;
		cont++;
	}
	return (array);
}
