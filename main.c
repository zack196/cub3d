#include "cub3d.h"

int	creat_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (1);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub");
	if (!cub->mlx_win)
		return (free(cub->mlx), 1);
	cub->image.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->image.addr = mlx_get_data_addr(cub->image.img
		, &cub->image.bits_per_pixel, &cub->image.line_length, &cub->image.endian);
	mlx_hook(cub->mlx_win, 2, (1L<<0), pres_bouton, cub);
	mlx_hook(cub->mlx_win, 3, (1L<<1), release_bouton, cub);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->line_length + y * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main()
{
	t_cub	cub;

	// parcing_map
	cub.map = tmp_map(&cub);
	sizing_map(&cub);

	//player initialisation
	player_init(&cub);

    cub.rays = my_malloc(sizeof (t_ray) * NBR_RAYS, 0);
	send_rays(&cub);

	// walls calculations
	// wall_calculations(&cub);

	// mlx handling
	if (creat_mlx(&cub))
		return (my_free(), 1);

	//render game
	render_walls(&cub);
	render_map(&cub);
	render_player(&cub);
	render_rays(&cub);
	
	mlx_loop(cub.mlx);
	my_free();
	return (0);
}