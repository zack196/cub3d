/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:53:26 by hel-band          #+#    #+#             */
/*   Updated: 2024/10/18 11:53:43 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char	*dst, const char *str, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(str));
	i = 0;
	while (str[i] && i < dstsize - 1)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(str));
}
