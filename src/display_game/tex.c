/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:33 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/15 19:45:25 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

void load_textures(t_data *data)
{
    data->textures[0].img = mlx_xpm_file_to_image(data->mlx
		, data->carte.north_texture
		, &data->textures[0].width, &data->textures[0].height);
    data->textures[1].img = mlx_xpm_file_to_image(data->mlx
		, data->carte.south_texture, &data->textures[1].width
		, &data->textures[1].height);
    data->textures[2].img = mlx_xpm_file_to_image(data->mlx
		, data->carte.east_texture, &data->textures[2].width
		, &data->textures[2].height);
    data->textures[3].img = mlx_xpm_file_to_image(data->mlx
		, data->carte.west_texture, &data->textures[3].width
		, &data->textures[3].height);
    // Extract texture data from the image
    data->textures[0].addr = mlx_get_data_addr(data->textures[0].img
		, &data->textures[0].bits_per_pixel, &data->textures[0].line_length 
		, &data->textures[0].endian);
    data->textures[1].addr = mlx_get_data_addr(data->textures[1].img
		, &data->textures[1].bits_per_pixel, &data->textures[1].line_length
		, &data->textures[1].endian);
    data->textures[2].addr = mlx_get_data_addr(data->textures[2].img
		, &data->textures[2].bits_per_pixel, &data->textures[2].line_length
		, &data->textures[2].endian);
    data->textures[3].addr = mlx_get_data_addr(data->textures[3].img
		, &data->textures[3].bits_per_pixel, &data->textures[3].line_length
		, &data->textures[3].endian);
}

int get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
    char	*dst;
	
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height) {
    fprintf(stderr, "Error: Texture access out of bounds at (%d, %d).\n", tex_x, tex_y);
    return -1;
}
	dst = tex->addr + (tex_x * tex->line_length + tex_y * (tex->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void render_textured_wall(t_data *data, int x, int y, t_ray *ray, float wall_height)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	t_texture		*tex;

	if (ray->ray_facing_up && ray->is_hit_vertical)
		tex = &data->textures[0];
	else if (!ray->ray_facing_up && ray->is_hit_vertical)
		tex = &data->textures[1];
	else if (ray->ray_facing_right && !ray->is_hit_vertical)
		tex = &data->textures[2];
	else
		tex = &data->textures[3];
	if (ray->is_hit_vertical)
		tex_y = (int)ray->hit_coord.y % data->tile_size;
	else
		tex_y = (int)ray->hit_coord.x % data->tile_size;
	if ((x - (data->win_height - wall_height) / 2) < 0)
		x = (data->win_height - wall_height) / 2;
	tex_x = (int)((x - (data->win_height - wall_height) / 2) * ((float) data->tile_size / wall_height)) % data->tile_size;
	color = get_texture_color(tex, tex_x, tex_y);
	my_mlx_pixel_put(&data->image, x, y, color);
}
