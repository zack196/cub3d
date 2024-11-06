#include "../../include/cub3d.h"

float   angle_normalize(float angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return (angle);
}

int is_wall(t_data *data, int x, int y)
{
    int x_map_coor;
    int y_map_coor;

    x_map_coor = x / data->tile_size;
    y_map_coor = y / data->tile_size;
    if (data->carte.cub[x_map_coor][y_map_coor] == '1')
        return (1);
    return (0);
}

float   init_player_rotation(t_data *data)
{
    float   angle;

    if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'E')
        angle = 0;
    else if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'S')
        angle = M_PI_2;
    else if (data->carte.cub[data->carte.player.x][data->carte.player.y] == 'W')
        angle = M_PI;
    else
        angle = 3 * M_PI_2;
    return (angle);
}

void draw_line(t_image *img, t_vector origine, t_vector end, int color)
{
    float dx = end.x - origine.x;
    float dy = end.y - origine.y;;
    int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = origine.x;
    float y = origine.y;
    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(img, (int)round(x), (int)round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (x * image->line_length + y * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}