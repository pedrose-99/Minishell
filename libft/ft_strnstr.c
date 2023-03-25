/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/14 10:51:21 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned long int		c1;
	unsigned long int		c2;

	if (to_find[0] == '\0')
		return ((char *)str);
	if (len == 0 && !str)
		return (0);
	c1 = 0;
	while (c1 < len && str[c1] != '\0')
	{
		c2 = 0;
		if ((str[c1 + c2]) && str[c1 + c2] == to_find[c2])
		{
			while ((str[c1 + c2])
				&& (str[c1 + c2] == to_find[c2]) && (c1 + c2) < len)
			{
				c2++;
				if (to_find[c2] == '\0')
					return ((char *)&str[c1]);
			}
		}
	c1++;
	}
	return (0);
}
