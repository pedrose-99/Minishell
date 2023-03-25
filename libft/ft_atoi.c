/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/19 09:20:44 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long int	result;
	int						sign;
	int						c;

	result = 0;
	sign = 1;
	c = 0;
	while (str[c] == 32 || (str[c] > 8 && str[c] < 14))
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			sign = -1;
		c++;
	}
	while (str[c] > 47 && str[c] < 58)
	{
		result = result * 10 + (str[c] - '0');
		c++;
	}
	if (result > 2147483647 && sign == 1)
		return (-1);
	else if (result > 2147483648 && sign == -1)
		return (0);
	return (sign * result);
}
