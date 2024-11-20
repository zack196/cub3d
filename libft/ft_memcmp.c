/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:54:10 by hel-band          #+#    #+#             */
/*   Updated: 2024/10/18 11:53:43 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*dst;
	size_t			i;

	if (!n)
		return (0);
	i = 0;
	str = (unsigned char *)s1;
	dst = (unsigned char *)s2;
	while (i < n && str[i] == dst[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (str[i] - dst[i]);
}
