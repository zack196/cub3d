#include "../include/cub3d.h"



void	mini_map(t_data *data)
{
	int	player_map_x;
	int	player_map_y;
	int	mini_map_height;
	int	mini_map_width;
	int	x_map;
	int	y_map;
	int	x_map_begin;
	int	y_map_begin;
	int	x;
	int	y;
	int	tile_size;

	tile_size = 20;
	player_map_x = data->player->player_coor.x / data->tile_size;
	player_map_y = data->player->player_coor.y / data->tile_size;
	mini_map_height = 400;
	mini_map_width = 400;
	x_map_begin = player_map_x - (mini_map_height / tile_size) / 2;
	if (player_map_x < (mini_map_height / tile_size) / 2)
		x_map_begin = 0;
	y_map_begin = player_map_y - (mini_map_width / tile_size) / 2;
	if (player_map_y < (mini_map_width / tile_size) / 2)
		y_map_begin = 0;
	
	x = -1;
	while (++x < mini_map_height)
	{
		y = -1;
		while (++y < mini_map_width)
		{
			x_map = x / tile_size + x_map_begin;
			y_map = y / tile_size + y_map_begin;
			if (x_map >= data->carte.row
				|| y_map >= ft_strlen(data->carte.cub[x_map]) 
				|| data->carte.cub[x_map][y_map] == '1')
				my_mlx_pixel_put(&data->image, x, y, 0X696969);
			else if (x_map == player_map_x && y_map == player_map_y)
				my_mlx_pixel_put(&data->image, x, y, 0X007AFF);
			else
				my_mlx_pixel_put(&data->image, x, y, 0XFFFFFF);
		}
	}
}
