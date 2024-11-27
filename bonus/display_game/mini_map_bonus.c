/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:51:46 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/27 17:12:50 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

t_vector	map_begin(t_data *data)
{
	t_vector	vec;

	data->player->player_map.x = data->player->player_coor.x
		/ data->tile_size;
	data->player->player_map.y = data->player->player_coor.y
		/ data->tile_size;
	vec.x = data->player->player_map.x - (data->mini_map_height
			/ data->mini_tile_size) / 2;
	if (vec.x < 0)
		vec.x = 0;
	vec.y = data->player->player_map.y - (data->mini_map_width
			/ data->mini_tile_size) / 2;
	if (vec.y < 0)
		vec.y = 0;
	return (vec);
}

int	is_mini_wall(t_data *data, int x, int y)
{
	t_vector	map_begin_coor;
	int			x_map;
	int			y_map;

	map_begin_coor = map_begin(data);
	x_map = x / data->mini_tile_size + map_begin_coor.x;
	y_map = y / data->mini_tile_size + map_begin_coor.y;
	if (x_map >= data->carte.row || y_map >= ft_strlen(data->carte.cub[x_map])
		|| data->carte.cub[x_map][y_map] == '1'
		|| data->carte.cub[x_map][y_map] == ' ')
		return (1);
	if (x_map == data->player->player_map.x
		&& y_map == data->player->player_map.y)
		return (2);
	if (data->carte.cub[x_map][y_map] == 'D')
		return (3);
	return (0);
}

void	mini_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->mini_map_height)
	{
		y = -1;
		while (++y < data->mini_map_width)
		{
			if (is_mini_wall(data, x, y) == 1)
				my_mlx_pixel_put(&data->image, x, y, 0X696969);
			else if (is_mini_wall(data, x, y) == 2)
				my_mlx_pixel_put(&data->image, x, y, 0XFF7AFF);
			else if (is_mini_wall(data, x, y) == 3)
				my_mlx_pixel_put(&data->image, x, y, 0X587AF0);
			else if (!(x % data->mini_tile_size) || !(y % data->mini_tile_size))
				my_mlx_pixel_put(&data->image, x, y, 0X007AFF);
			else
				my_mlx_pixel_put(&data->image, x, y, 0XFFFFFF);
		}
	}
}
