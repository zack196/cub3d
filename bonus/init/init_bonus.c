/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:42:45 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/20 04:09:40 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_color(t_color *color)
{
	color->red = -1;
	color->green = -1;
	color->blue = -1;
}
void	ft_init_carte(t_map *map)
{
	map->cub= NULL;
	map->row = -1;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->filename = NULL;
	map->starting_derection = '\0';
	init_color(&map->floor_color);
	init_color(&map->ceilling_color);
	map->player.x = 0;
	map->player.y = 0;
}
void	ft_init_game(t_data *data)
{
	int	i;

	ft_init_carte(&data->carte);
	//mlx init
	data->mlx = NULL;
	data->win_ptr = NULL;
	data->image.img = NULL;
	i = -1;
	while (++i < 4)
		data->textures[i].img = NULL;
}