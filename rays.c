#include "cub3d.h"

void	ray_facing(t_ray *ray)
{
	ray->ray_facing_up = 1;
	if (ray->angle <= M_PI)
		ray->ray_facing_up = 0;
	ray->ray_facing_right = 0;
	if (ray->angle <= M_PI_2 || ray->angle >= 3 * M_PI_2)
		ray->ray_facing_right = 1;
}

float   vertical_wall_hit_distance(t_ray *ray, t_cub *cub)
{
	float	x_step;
	float	y_step;
	float	x_intersection;
	float	y_intersection;

	x_intersection = floor(cub->player->x_player / cub->tile_size
		+ !ray->ray_facing_up) * cub->tile_size;
	y_intersection = cub->player->y_player + (x_intersection
		- cub->player->x_player) / tan(ray->angle);
	x_step = (1 - 2 * ray->ray_facing_up) * cub->tile_size;
	y_step = x_step / tan(ray->angle);
	while (x_intersection > 0 && y_intersection > 0 && x_intersection < cub->map_window_height
		&& y_intersection < cub->map_window_width)
	{
		if (is_wall(cub, x_intersection - ray->ray_facing_up
			+ !ray->ray_facing_up, y_intersection))
			break ;
		x_intersection += x_step;
		y_intersection += y_step;
	}
	return (sqrt(pow(cub->player->x_player - x_intersection, 2)
		+ pow(cub->player->y_player - y_intersection, 2)));
}

float	horizontal_wall_hit_distace(t_ray *ray, t_cub *cub)
{
	float	x_step;
	float	y_step;
	float	x_intersection;
	float	y_intersection;

	y_intersection = floor(cub->player->y_player / cub->tile_size
		+ ray->ray_facing_right) * cub->tile_size;
	x_intersection = cub->player->x_player + (y_intersection
		- cub->player->y_player) * tan(ray->angle);
	y_step = (1 - 2 * !ray->ray_facing_right) * cub->tile_size;
	x_step = y_step * tan(ray->angle);
	while (x_intersection > 0 && y_intersection > 0 && x_intersection < cub->map_window_height
		&& y_intersection < cub->map_window_width)
	{
		if (is_wall(cub, (int)x_intersection, (int)(y_intersection
			+ ray->ray_facing_right - !ray->ray_facing_right)))
				break ;
		x_intersection += x_step;
		y_intersection += y_step;
	}
	return (sqrt(pow(cub->player->x_player - x_intersection, 2)
		+ pow(cub->player->y_player - y_intersection, 2)));
}

void    send_rays(t_cub *cub)
{
	t_ray	*rays;
	float	angle;
	int		i;

	angle = cub->player->rotation_angle - FOV_ANGLE / 2;
	rays = cub->rays;
	i = -1;
	while (++i < NBR_RAYS)
	{
		rays[i].angle = angle_normalize(angle);
		ray_facing(&rays[i]);
			rays[i].distance = fminf(vertical_wall_hit_distance(&rays[i], cub)
				, horizontal_wall_hit_distace(&rays[i], cub));
		angle += FOV_ANGLE / NBR_RAYS;
	}
}
