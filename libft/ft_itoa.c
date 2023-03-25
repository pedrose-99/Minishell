/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/14 10:48:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(unsigned int n)
{
	unsigned int	first_block;
	int				cont;

	first_block = n;
	cont = 1;
	while (first_block >= 10)
	{
		first_block = first_block / 10;
		cont++;
	}
	return (cont);
}

static char	*fill_arr(char *array, unsigned int first_block, int n, int len_num)
{
	unsigned int	rem;

	if (n < 0)
	{
		array[0] = '-';
	}
	array[len_num] = '\0';
	len_num--;
	while (first_block >= 10)
	{
		rem = first_block % 10;
		first_block = first_block / 10;
		array[len_num] = rem + '0';
		len_num--;
	}
	array[len_num] = first_block + '0';
	return (array);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				num_elem;
	char			*array;

	nb = n;
	if (n < 0)
		nb = n * -1;
	num_elem = num_len(nb);
	if (n < 0)
		num_elem++;
	array = (char *)malloc(sizeof(char) * (num_elem + 1));
	if (array == NULL)
		return (NULL);
	array = fill_arr(array, nb, n, num_elem);
	return (array);
}
