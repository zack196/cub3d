/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:58:18 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/27 08:22:39 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_walls(t_data *data)
{
	int		x;
	int		y;
	float	ply_projection_plane;
	float	wall_height;
	float	player_wall_distance;

	y = -1;
	ply_projection_plane = data->win_width / (2 * tan(data->fov_angle / 2));
	while (++y < data->win_width)
	{
		player_wall_distance = data->rays[y].distance * cos(data->rays[y].angle
				- data->player->player_rotation);
		wall_height = (data->tile_size * ply_projection_plane)
			/ player_wall_distance;
		x = -1;
		while (++x < data->win_height)
		{
			if ((data->win_height - wall_height) / 2 > x)
				my_mlx_pixel_put(&data->image, x, y, data->ceiling_color);
			else if (x < (data->win_height + wall_height) / 2)
				render_textured_wall(data, x, y, wall_height);
			else
				my_mlx_pixel_put(&data->image, x, y, data->floor_color);
		}
	}
}

int	render_game(t_data *data)
{
	render_walls(data);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->image.img, 0, 0);
	return (0);
}
