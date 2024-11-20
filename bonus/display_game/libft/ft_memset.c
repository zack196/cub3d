/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:40:33 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/13 18:12:04 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	uc;

	i = 0;
	str = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		str[i] = uc;
		i++;
	}
	return (s);
}