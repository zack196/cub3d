/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:11:56 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/21 22:11:57 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	angle_normalize(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	is_wall(t_data *data, int x, int y)
{
	int	x_map_coor;
	int	y_map_coor;

	x_map_coor = x / data->tile_size;
	y_map_coor = y / data->tile_size;
	if (x_map_coor >= data->carte.row
		|| y_map_coor >= ft_strlen(data->carte.cub[x_map_coor]))
		return (1);
	if (!ft_strchr("0NEWS", data->carte.cub[x_map_coor][y_map_coor]))
		return (1);
	return (0);
}

float	init_player_rotation(t_data *data)
{
	float	angle;

	if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'E')
		angle = 0;
	else if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'S')
		angle = M_PI_2;
	else if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'W')
		angle = M_PI;
	else
		angle = 3 * M_PI_2;
	return (angle);
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (x * image->line_length + y
			* (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	distance(t_vector a, t_float_vector b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}
