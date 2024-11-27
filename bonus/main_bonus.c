/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:26:05 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 17:13:46 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_parsing(t_data *data)
{
	if (ft_find_cub_(data->carte.filename, ".cub") == EXIT_FAILURE)
		print_error("", "Wrong extention.", 1);
	ft_pars_map(data);
	ft_find_content(data);
	ft_add_textures(data);
	ft_add_colors(data);
	ft_take_cub(data);
	ft_find_player_pos(&(data)->carte);
	ft_pars_cub(data->carte.cub, data);
	ft_last_pars_cub(data->carte);
}

void	hook_handel(t_data *data)
{
	mlx_mouse_hook(data->win_ptr, pres_mousse, data);
	mlx_hook(data->win_ptr, 2, (1L << 0), pres_bouton, data);
	mlx_hook(data->win_ptr, 3, (1L << 1), release_bouton, data);
	mlx_hook(data->win_ptr, 17, 0L, clear_all, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move_hook, data);
}

int	display_game(t_data *data)
{
	init_mlx(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"cub");
	if (!data->win_ptr)
		return (1);
	data->image.img = mlx_new_image(data->win_ptr, data->win_width,
			data->win_height);
	if (!data->image.img)
		return (1);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel, &data->image.line_length,
			&data->image.endian);
	if (!data->image.addr)
		return (1);
	init_sprite(data);
	if (load_textures(data) || load_sprite(data))
		return (1);
	hook_handel(data);
	return (0);
}

int	clear_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (data->textures[i].img)
			mlx_destroy_image(data->mlx, data->textures[i].img);
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx, data->win_ptr);
	my_free();
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		print_error(*av, "numberd argument not valid\n", 1);
	ft_init_game(&data);
	data.carte.filename = ft_strdup(av[1]);
	if (!data.carte.filename)
		return (1);
	ft_parsing(&data);
	init_game(&data);
	if (display_game(&data))
		return (clear_all(&data), 1);
	render_game(&data);
	mlx_loop(data.mlx);
	clear_all(&data);
	return (0);
}
