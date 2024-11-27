/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:49:11 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:47:48 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen || len == 0)
		return (ft_calloc(1, 1));
	if (slen - start <= len)
		len = slen - start;
	dst = my_malloc(len + 1, 0);
	i = 0;
	while (s[start] && i < len)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}
