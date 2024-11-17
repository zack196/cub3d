#include "../../include/cub3d.h"

void	render_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->map_height)
	{
		y = -1;
		while (++y < data->map_width)
		{
			if (is_wall(data, x, y))
				my_mlx_pixel_put(&data->image, x, y, 0X696969);
			else
				my_mlx_pixel_put(&data->image, x, y, 0XFFFFFF);
		}
	}
}

void	render_player(t_data *data)
{
	int			x_player;
	int			y_player;
	int			x;
	int			y;
	t_vector	end;

	x_player = data->player->player_coor.x; 
	y_player = data->player->player_coor.y;
	x = -1;
	while (++x < data->map_height)
	{
		y = -1;
		while (++y < data->map_width)
			if (sqrt(pow(x_player - x, 2) + pow(y_player - y, 2)) < 5 * MAP_SCALE)
					my_mlx_pixel_put(&data->image, x, y, 0X007AFF);
	}
	end.x = x_player + 25 * MAP_SCALE * sin(data->player->player_rotation);
	end.y = y_player + 25 * MAP_SCALE * cos(data->player->player_rotation);
	draw_line(&data->image, data->player->player_coor, end, 0XF20002);
}

void	render_rays(t_data *data)
{
	int			i;
	t_vector	end;

	i = -1;
	while (++i < data->nbr_rays)
	{
		end.x = data->player->player_coor.x +  sin(data->rays[i].angle) * data->rays[i].distance;
		end.y = data->player->player_coor.y +  cos(data->rays[i].angle) * data->rays[i].distance;
		draw_line(&data->image, data->player->player_coor, end, 0X87CEEB);
	}
}

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
				my_mlx_pixel_put(&data->image, x, y, 0X1E90FF);
			else if (x < (data->win_height + wall_height) / 2)
				render_textured_wall(data, x, y, &data->rays[y], wall_height);
			else
				my_mlx_pixel_put(&data->image, x, y, 0XA9A9A9);
		}
	}
}

int    render_game(t_data *data)
{
	// mlx_clear_window(data->mlx, data->win_ptr);
	render_walls(data);
	// render_map(data);
	// render_rays(data);
	// render_player(data);
	mlx_put_image_to_window(data->mlx, data->win_ptr, data->image.img, 0, 0);
	return (0);
}