/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:40:33 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:48:42 by zel-oirg         ###   ########.fr       */
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
