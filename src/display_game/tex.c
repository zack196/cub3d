/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:21:33 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/11 14:53:53 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

// Function to load textures from file paths
void load_textures(t_data *data)
{
    data->textures[0].img = mlx_xpm_file_to_image(data->mlx, data->carte.north_texture, &data->textures[0].width, &data->textures[0].height);
    data->textures[1].img = mlx_xpm_file_to_image(data->mlx, data->carte.south_texture, &data->textures[1].width, &data->textures[1].height);
    data->textures[2].img = mlx_xpm_file_to_image(data->mlx, data->carte.east_texture, &data->textures[2].width, &data->textures[2].height);
    data->textures[3].img = mlx_xpm_file_to_image(data->mlx, data->carte.west_texture, &data->textures[3].width, &data->textures[3].height);

    // Extract texture data from the image
    data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel, &data->textures[0].line_length, &data->textures[0].endian);
    data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel, &data->textures[1].line_length, &data->textures[1].endian);
    data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel, &data->textures[2].line_length, &data->textures[2].endian);
    data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel, &data->textures[3].line_length, &data->textures[3].endian);
}

// Function to calculate the correct texture coordinate based on ray hit position
int get_texture_color(t_data *data, t_ray *ray, int x, int y)
{
    int tex_x;
    int tex_y;
    int color;

    // For vertical walls (x-coordinates), use the appropriate texture
    if (ray->is_hit_vertical)
    {
        tex_x = (int)(y / data->tile_size) % data->textures[0].width;
        if (ray->ray_facing_up)
            tex_y = (int)((x - floor(x / data->tile_size) * data->tile_size) / data->tile_size * data->textures[0].height);
        else
            tex_y = (int)((x - floor(x / data->tile_size) * data->tile_size) / data->tile_size * data->textures[1].height);
    }
    // For horizontal walls (y-coordinates), use the appropriate texture
    else
    {
        tex_y = (int)(x / data->tile_size) % data->textures[0].height;
        if (ray->ray_facing_right)
            tex_x = (int)((y - floor(y / data->tile_size) * data->tile_size) / data->tile_size * data->textures[2].width);
        else
            tex_x = (int)((y - floor(y / data->tile_size) * data->tile_size) / data->tile_size * data->textures[3].width);
    }

    // Get the pixel color from the texture at (tex_x, tex_y)
    color = *(int *)(data->textures[0].addr + (tex_y * data->textures[0].line_length + tex_x * (data->textures[0].bits_per_pixel / 8)));
    return color;
}

// Function to render the walls with the textures
void render_textured_wall(t_data *data, int column, float distance, float wall_height)
{
    int x;
    int y;
    int tex_color;
    int wall_top = (data->win_height - wall_height) / 2;
    int wall_bottom = (data->win_height + wall_height) / 2;

    y = wall_top;
    while (y < wall_bottom)
    {
        // Determine texture coordinate and color for the wall pixel
        tex_color = get_texture_color(data, &data->rays[column], column, y);
        // Draw the pixel
        my_mlx_pixel_put(&data->image, column, y, tex_color);
        y++;
    }
}
