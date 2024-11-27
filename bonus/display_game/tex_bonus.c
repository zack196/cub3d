/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:33 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 08:34:43 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	load_textures(t_data *data)
{
	int	i;

	data->textures[0].tex_name = data->carte.north_texture;
	data->textures[1].tex_name = data->carte.south_texture;
	data->textures[2].tex_name = data->carte.east_texture;
	data->textures[3].tex_name = data->carte.west_texture;
	data->textures[4].tex_name = "textures/door_texture.xpm";
	i = -1;
	while (++i < 5)
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->mlx,
				data->textures[i].tex_name,
				&data->textures[i].width, &data->textures[i].height);
		if (!data->textures[i].img)
			return (1);
		data->textures[i].addr = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].line_length,
				&data->textures[i].endian);
		if (!data->textures[i].addr)
			return (1);
	}
	return (0);
}

int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*dst;

	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (-1);
	dst = tex->addr + (tex_x * tex->line_length + tex_y
			* (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	textured_wall(t_data *data, int x, int y, float wall_height)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	t_texture		*tex;

	if (data->rays[y].is_door)
		tex = &data->textures[4];
	else if (data->rays[y].ray_facing_up && data->rays[y].is_hit_vertical)
		tex = &data->textures[0];
	else if (!data->rays[y].ray_facing_up && data->rays[y].is_hit_vertical)
		tex = &data->textures[1];
	else if (data->rays[y].ray_facing_right && !data->rays[y].is_hit_vertical)
		tex = &data->textures[2];
	else
		tex = &data->textures[3];
	if (data->rays[y].is_hit_vertical)
		tex_y = (int)data->rays[y].hit_coord.y % data->tile_size;
	else
		tex_y = (int)data->rays[y].hit_coord.x % data->tile_size;
	if ((x - (data->win_height - wall_height) / 2) < 0)
		x = (data->win_height - wall_height) / 2;
	tex_x = (int)((x - (data->win_height - wall_height) / 2)
			* ((float) data->tile_size / wall_height)) % data->tile_size;
	color = get_texture_color(tex, tex_x, tex_y);
	my_mlx_pixel_put(&data->image, x, y, color);
}
