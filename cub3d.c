#include "cub3d.h"

int	init_display(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (1);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->mlx_win)
		return (free(cub->mlx), 1);
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img.img)
		return (/*mlx_destroy_display(cub->mlx),*/ 1);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel
		, &cub->img.line_length, &cub->img.endian);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (printf("error input\n"), 1);
	if (parce_cub(&cub, av[1]))
		return (my_free(), 1);
	if (init_display(&cub))
		return (my_free(), 1);
	
	mlx_loop(cub.mlx);
	my_free();
	return (0);
}
