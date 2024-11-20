/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:36:48 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/20 04:41:37 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_intlen(long long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (++i);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int m)
{
	size_t		i;
	char		*str;
	long long	n;

	n = m;
	i = ft_intlen(n);
	str = my_malloc(i + 1, 0);
	str[i] = '\0';
	if (n == 0)
		str[0] = 48;
	else if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[--i] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}
