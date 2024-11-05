#include "cub3d.h"

int is_wall(t_cub *cub, int x, int y)
{
    int x_map_coor;
    int y_map_coor;

    x_map_coor = x / cub->tile_size;
    y_map_coor = y / cub->tile_size;
    if (cub->map[x_map_coor][y_map_coor] == '1')
        return (1);
    return (0);
}

void	render_map(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	while (++x < cub->map_window_height)
	{
		y = -1;
		while (++y < cub->map_window_width)
		{
			if (is_wall(cub, x, y))
				my_mlx_pixel_put(&cub->image, x, y, 0X696969);
			else
			    my_mlx_pixel_put(&cub->image, x, y, 0XFFFFFF);
		}
	}
	// mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->image.img, 0, 0);
}

void	render_player(t_cub *cub)
{
	int	x;
	int	y;
	int	x_player;
	int	y_player;

	x_player = cub->player->x_player;
	y_player = cub->player->y_player;
	x = -1;
	while (++x < cub->map_window_height)
	{
		y = -1;
		while (++y < cub->map_window_width)
		{
			if (sqrt(pow(x_player - x, 2) + pow(y_player - y, 2)) < 9 * MAP_SCALE)
				my_mlx_pixel_put(&cub->image, x, y, 0X007AFF);
		}
	}
	draw_line(&cub->image, x_player, y_player
		, x_player + 25 * MAP_SCALE * sin(cub->player->rotation_angle)
		, y_player + 25 * MAP_SCALE * cos(cub->player->rotation_angle)
		, 0XF20002);
}

void	render_rays(t_cub *cub)
{
	t_ray	ray;
	int		i;

	i = -1;
	while (++i < NBR_RAYS)
	{
		ray = cub->rays[i];
		draw_line(&cub->image, cub->player->x_player, cub->player->y_player
            , cub->player->x_player + sin(ray.angle) * ray.distance
            , cub->player->y_player + cos(ray.angle) * ray.distance,
            0X87CEEB);
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->image.img, 0, 0);
}

void	render_walls(t_cub *cub)
{
	int		x;
	int		y;
	float	ply_projection_plane;
	float	wall_height;

	y = -1;
	ply_projection_plane = WIDTH / (2 * tan(FOV_ANGLE / 2));
	while (++y < WIDTH)
	{
		wall_height = (cub->tile_size * ply_projection_plane) / cub->rays[y].distance;
		x = -1;
		while (++x < HEIGHT)
		{
			if ((HEIGHT - wall_height) / 2 > x)
				my_mlx_pixel_put(&cub->image, x, y, cub->floor_color);
			else if (x > (HEIGHT + wall_height) / 2)
				my_mlx_pixel_put(&cub->image, x, y, cub->ceiling_color);
			else
				my_mlx_pixel_put(&cub->image, x, y, 0XA9A9A9);
		}
	}
}
