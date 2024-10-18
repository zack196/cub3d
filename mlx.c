#include "cub3d.h"

void	mov_player(t_cub *cub, int up, int down, int left, int right)
{
	cub->player->player_x = down - up;
	cub->player->player_y = right - left;
}

int	key_pres(int button, t_cub *cub)
{
	if (button == 13)//up
		mov_player(cub, 1, 0, 0, 0);
	else if (button == 0)//left
		mov_player(cub, 0, 0, 1, 0);
	else if (button == 1)//down
		mov_player(cub, 0, 1, 0, 0);
	else if (button == 2)//right
		mov_player(cub, 0, 0, 0, 1);
	else if (button == 124)//turn right
		mov_player(cub, 0, 0, 0, 1);
	else if (button == 123)//turn left
		mov_player(cub, 0, 0, 0, 1);
	render_cub(cub);
	printf("%d\n", button);
	return (1);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	mlx_handel(t_cub *cub)
{
	cub->mlx = mlx_init();
    if (!cub->mlx)
        return (1);
	cub->win_mlx = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->win_mlx)
		return (1);//destroy_display
	cub->image.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image.img)
		return (mlx_destroy_window(cub->mlx, cub->win_mlx), 1);
	cub->image.addr = mlx_get_data_addr(cub->image.img
		, &cub->image.bits_per_pixel, &cub->image.line_length
		, &cub->image.endian);
	mlx_key_hook(cub->win_mlx, key_pres, cub);
	return (0);
}
