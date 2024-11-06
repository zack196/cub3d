#include "../../include/cub3d.h"

void	ray_facing(t_ray *ray)
{
	ray->ray_facing_up = 1;
	if (ray->angle <= M_PI)
		ray->ray_facing_up = 0;
	ray->ray_facing_right = 0;
	if (ray->angle <= M_PI_2 || ray->angle >= 3 * M_PI_2)
		ray->ray_facing_right = 1;
}

float   vertical_wall_hit_distance(t_ray *ray, t_data *data)
{
	float	x_step;
	float	y_step;
	float	x_intersection;
	float	y_intersection;

	x_intersection = floor(data->player->player_coor.x / data->tile_size
		+ !ray->ray_facing_up) * data->tile_size;
	y_intersection = data->player->player_coor.y + (x_intersection
		- data->player->player_coor.x) / tan(ray->angle);
	x_step = (1 - 2 * ray->ray_facing_up) * data->tile_size;
	y_step = x_step / tan(ray->angle);
	while (x_intersection > 0 && y_intersection > 0 && x_intersection
        < data->mini_map_window_height && y_intersection
        < data->mini_map_window_width)
	{
		if (is_wall(data, x_intersection - ray->ray_facing_up
			+ !ray->ray_facing_up, y_intersection))
			break ;
		x_intersection += x_step;
		y_intersection += y_step;
	}
	return (sqrt(pow(data->player->player_coor.x - x_intersection, 2)
		+ pow(data->player->player_coor.y - y_intersection, 2)));
}

float	horizontal_wall_hit_distace(t_ray *ray, t_data *data)
{
	float	x_step;
	float	y_step;
	float	x_intersection;
	float	y_intersection;

	y_intersection = floor(data->player->player_coor.y / data->tile_size
		+ ray->ray_facing_right) * data->tile_size;
	x_intersection = data->player->player_coor.x + (y_intersection
		- data->player->player_coor.y) * tan(ray->angle);
	y_step = (1 - 2 * !ray->ray_facing_right) * data->tile_size;
	x_step = y_step * tan(ray->angle);
	while (x_intersection > 0 && y_intersection > 0 && x_intersection
        < data->mini_map_window_height && y_intersection
        < data->mini_map_window_width)
	{
		if (is_wall(data, (int)x_intersection, (int)(y_intersection
			+ ray->ray_facing_right - !ray->ray_facing_right)))
				break ;
		x_intersection += x_step;
		y_intersection += y_step;
	}
	return (sqrt(pow(data->player->player_coor.x - x_intersection, 2)
		+ pow(data->player->player_coor.y - y_intersection, 2)));
}

void    send_rays(t_data *data)
{
    int     i;
    float   angle;

    i = -1;
    angle = data->player->player_rotation - data->fov_angle / 2;
    while (++i < data->nbr_rays)
    {
        data->rays[i].angle = angle_normalize(angle);
        ray_facing(&data->rays[i]);
			data->rays[i].distance = 
            fminf(vertical_wall_hit_distance(&data->rays[i], data)
			, horizontal_wall_hit_distace(&data->rays[i], data));
        angle += data->fov_angle / data->nbr_rays;
    }
}
