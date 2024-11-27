/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:01:40 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:47:57 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	size_t	s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy = my_malloc(sizeof(char) * (s1_len + 1), 0);
	while (s1[i] && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
