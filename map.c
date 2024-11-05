/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:35:34 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/05 09:21:28 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sizing_map(t_cub *cub)
{
    int		i;
    char	**map;

	map = cub->map;
	cub->map_width = 0;
    i = 0;
    while (map[i])
	{
		if (cub->map_width < (int)ft_strlen(map[i]))
			cub->map_width = ft_strlen(map[i]);
		i++;
	}
	cub->map_height = i;
	cub->tile_size = MAP_SCALE * (int)fmin((float)WIDTH
		/ cub->map_width, (float)HEIGHT / cub->map_height);
	cub->map_window_height = cub->tile_size * cub->map_height;
	cub->map_window_width = cub->tile_size * cub->map_width;
}

char	**tmp_map(t_cub *cub)
{
	char	**map;

	map = my_malloc(sizeof (char *) * 16, 0);
	map[0] = ft_strdup("11111111111111111111111111111111111111111111111111111");
	map[1] = ft_strdup("11000000000000000000000000000000000010000000000000111");
	map[2] = ft_strdup("11011100000000000000000000000000000010000000000001111");
	map[3] = ft_strdup("111101N0000000100000100000000000000010000000000001111");
	map[4] = ft_strdup("11001100000000000000000000000000000010000000000000111");
	map[5] = ft_strdup("11000001111110111111111111110100000010000000000111111");
	map[6] = ft_strdup("11001111111110111111111111110100000000000000000111111");
	map[7] = ft_strdup("11001100000000000001000000000000000000000000000000111");
	map[8] = ft_strdup("11101100000000000000000000000000000000000000000000111");
	map[9] = ft_strdup("11101000000000000001000000000000000010000000000000111");
	map[10] =ft_strdup("11100000000000000001000000000000000010000000000000111");
	map[11] =ft_strdup("11100000000000000001000000000000000010000000000000111");
	map[12] =ft_strdup("11100000000000000001000000000000000010000000000000111");
	map[13] =ft_strdup("11100000000000000001000000000000000010000000000000111");
	map[14] =ft_strdup("11111111111111111111111111111111111111111111111111111");
	map[15] = NULL;
	cub->ceiling_color = 0X1E90FF;
	cub->floor_color = 0X8B4513;
	return (map);
}

void draw_line(t_data *img, int x_origin, int y_origin, int x_end, int y_end, int color)
{
    float dx = x_end - x_origin;
    float dy = y_end - y_origin;
    int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy); // Determine the number of steps
    float x_inc = dx / steps; // Increment per step in x
    float y_inc = dy / steps; // Increment per step in y

    float x = x_origin;
    float y = y_origin;
    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(img, (int)round(x), (int)round(y), color);
        x += x_inc;
        y += y_inc;
    }
}
