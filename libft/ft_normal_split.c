/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:03:43 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:50:46 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_countworld(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			i++;
	}
	return (count);
}

size_t	ft_len(char const *str, char c)
{
	size_t	j;

	j = 0;
	while (str[j] && str[j] != c)
		j++;
	return (j);
}

char	*ft_world(char const *str, char c)
{
	char	*dst;
	size_t	i;

	dst = (char *)my_malloc((ft_len(str, c) + 1) * sizeof(char), 0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_normal_split(char *s, char c)
{
	char	**dst;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = ft_countworld(s, c);
	dst = (char **)my_malloc((ft_countworld(s, c) + 1) * sizeof(char *), 0);
	i = 0;
	while (*s && i < j)
	{
		while (*s == c)
			s++;
		dst[i] = ft_world(s, c);
		i++;
		while (*s != c && *s)
			s++;
	}
	dst[i] = 0;
	return (dst);
}
