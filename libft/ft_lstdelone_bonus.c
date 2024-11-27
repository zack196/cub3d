/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:10:27 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:51:12 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del) (void*))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
}
