/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:59:48 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:51:31 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_add(char **str, int i)
{
	char	*new;

	new = ft_substr(*str, i, ft_strlen(*str + i));
	*str = NULL;
	return (new);
}
