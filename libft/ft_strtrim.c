/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/14 11:00:47 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_set(char const c, char const *set)
{
	size_t	cont;

	cont = 0;
	while (set[cont])
	{
		if (c == set[cont])
			return (1);
		cont++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	cont;
	char	*string;
	size_t	p_left;
	size_t	p_right;

	cont = 0;
	p_left = 0;
	while (s1[p_left] && (char_set(s1[p_left], set) == 1))
		p_left++;
	p_right = ft_strlen(s1);
	while ((p_right > p_left) && (char_set(s1[p_right - 1], set) == 1))
		p_right--;
	string = (char *)malloc(sizeof(char) * (p_right - p_left) + 1);
	if (!string)
		return (NULL);
	while (p_left < p_right)
	{
		string[cont] = s1[p_left];
		cont++;
		p_left++;
	}
	string[cont] = '\0';
	return (string);
}
