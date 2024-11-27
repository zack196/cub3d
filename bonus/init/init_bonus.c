/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:42:45 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 10:51:40 by zel-oirg         ###   ########.fr       */
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
	map->cub = NULL;
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
	data->mlx = NULL;
	data->win_ptr = NULL;
	data->image.img = NULL;
	i = -1;
	while (++i < 4)
		data->textures[i].img = NULL;
}

void	init_game(t_data *data)
{
	data->open_door = 1;
	data->mouse_active = 0;
	data->mini_map_height = 400;
	data->mini_map_width = 400;
	data->mini_tile_size = 20;
	data->win_width = 1700;
	data->win_height = 1350;
	data->tile_size = 64;
	data->map_height = data->carte.row * data->tile_size;
	data->map_width = data->carte.col * data->tile_size;
	data->fov_angle = 60 * M_PI / 180;
	data->player = my_malloc(sizeof (t_player), 0);
	data->player->player_coor.x = data->tile_size * data->carte.player.x
		+ data->tile_size / 2;
	data->player->player_coor.y = data->tile_size * data->carte.player.y
		+ data->tile_size / 2;
	data->player->player_rotation = init_player_rotation(data);
	data->nbr_rays = data->win_width;
	data->rays = my_malloc(sizeof (t_ray) * data->nbr_rays, 0);
	send_rays(data);
}

void	init_mlx(t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->win_ptr = NULL;
	data->image.img = NULL;
	i = -1;
	while (++i < 4)
		data->textures[i].img = NULL;
}
