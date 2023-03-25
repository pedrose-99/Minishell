/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2022/10/14 11:03:22 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**make_array2d(char const *s, char c)
{
	char	**array_2d;
	int		cont;
	int		len;

	cont = 0;
	len = 0;
	while (s[cont] == c && s[cont])
			cont++;
	while (s[cont])
	{
		len++;
		while (s[cont] != c && s[cont])
			cont++;
		while (s[cont] == c && c != 0)
			cont++;
	}
	array_2d = (char **)malloc(sizeof(char *) * (len + 1));
	return (array_2d);
}

static void	free_array2d(char **array_2d, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(array_2d[j]);
		i++;
	}
	array_2d = NULL;
}

static void	fill_array2d(char **array_2d, char const *s, char c)
{
	int		i;
	int		j;
	int		word_size;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		word_size = 0;
		while (s[i + word_size] != c && s[i + word_size])
			word_size++;
		array_2d[j] = ft_substr(s, i, word_size);
		if (!array_2d[j])
		{
			free_array2d(array_2d, j);
			break ;
		}
		i = i + word_size;
		j++;
		while (s[i] == c && s[i])
			i++;
	}
	array_2d[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**array_2d;

	if (!s)
		return (NULL);
	array_2d = make_array2d(s, c);
	if (!array_2d)
		return (NULL);
	fill_array2d(array_2d, s, c);
	if (!array_2d)
		return (NULL);
	return (array_2d);
}
