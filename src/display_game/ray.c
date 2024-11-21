/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:16:07 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/21 22:20:33 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_float_vector	vertical_wall_hit_distance(t_ray *ray, t_data *data)
{
	float			x_step;
	float			y_step;
	t_float_vector	inter;

	inter.x = floor(data->player->player_coor.x / data->tile_size
			+ !ray->ray_facing_up) * data->tile_size;
	inter.y = data->player->player_coor.y + (inter.x
			- data->player->player_coor.x) / tan(ray->angle);
	x_step = (1 - 2 * ray->ray_facing_up) * data->tile_size;
	y_step = x_step / tan(ray->angle);
	while (inter.x > 0 && inter.y > 0 && inter.x
		< data->map_height && inter.y
		< data->map_width)
	{
		if (is_wall(data, (int)(inter.x - ray->ray_facing_up
				+ !ray->ray_facing_up), (int)inter.y))
			break ;
		inter.x += x_step;
		inter.y += y_step;
	}
	return (inter);
}

t_float_vector	horizontal_wall_hit_distace(t_ray *ray, t_data *data)
{
	float			x_step;
	float			y_step;
	t_float_vector	inter;

	inter.y = floor(data->player->player_coor.y / data->tile_size
			+ ray->ray_facing_right) * data->tile_size;
	inter.x = data->player->player_coor.x + (inter.y
			- data->player->player_coor.y) * tan(ray->angle);
	y_step = (1 - 2 * !ray->ray_facing_right) * data->tile_size;
	x_step = y_step * tan(ray->angle);
	while (inter.x > 0 && inter.y > 0 && inter.x
		< data->map_height && inter.y < data->map_width)
	{
		if (is_wall(data, (int)inter.x, (int)(inter.y
				+ ray->ray_facing_right - !ray->ray_facing_right)))
			break ;
		inter.x += x_step;
		inter.y += y_step;
	}
	return (inter);
}

void	get_rays_values(t_data *data, t_ray *ray, t_float_vector vert
	, t_float_vector horz)
{
	if (distance(data->player->player_coor, vert)
		> distance(data->player->player_coor, horz))
	{
		ray->distance = distance(data->player->player_coor, horz);
		ray->hit_coord = horz;
		ray->is_hit_vertical = 0;
	}
	else
	{
		ray->distance = distance(data->player->player_coor, vert);
		ray->hit_coord = vert;
		ray->is_hit_vertical = 1;
	}
}

void	send_rays(t_data *data)
{
	int				i;
	float			angle;
	t_float_vector	horz;
	t_float_vector	vert;

	i = -1;
	angle = data->player->player_rotation - data->fov_angle / 2;
	while (++i < data->nbr_rays)
	{
		data->rays[i].angle = angle_normalize(angle);
		ray_facing(&data->rays[i]);
		horz = horizontal_wall_hit_distace(&data->rays[i], data);
		vert = vertical_wall_hit_distance(&data->rays[i], data);
		get_rays_values(data, &data->rays[i], vert, horz);
		angle += data->fov_angle / data->nbr_rays;
	}
}
