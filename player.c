/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:50:57 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/10/18 03:42:09 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(char c)
{
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'W')
		return (1);
	else if (c == 'E')
		return (1);
	return (0);
}

void	get_player_position(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
			if (check_player(cub->map[i][j]))
				break ;
		if (check_player(cub->map[i][j]))
			break ;
	}
	cub->player->player_x = i;
	cub->player->player_y = j;
}
