/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:50:30 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/20 04:42:20 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	i;

	i = ft_strlen(s1);
	dest = my_malloc(i + 1, 0);
	ft_memcpy(dest, s1, i);
	dest[i] = '\0';
	return (dest);
}
