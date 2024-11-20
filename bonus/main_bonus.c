/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:26:05 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/20 05:05:09 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_parsing(t_data *data)
{
	if (ft_find_cub_(data->carte.filename, ".cub") == EXIT_FAILURE)
		print_error("","Wrong extention.",1);
	ft_pars_map(data);
	ft_find_content(data);
	ft_add_textures(data);
	ft_add_colors(data);
	ft_take_cub(data);
	ft_find_player_pos(&(data)->carte);
	ft_pars_cub(data->carte.cub, data);
	ft_last_pars_cub(data->carte);
}
void	init_mlx(t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->win_ptr = NULL;
	data->image.img = NULL;
	i = -1;
	while (++i < 4)
		data->textures[i].img = NULL;
}
int	display_game(t_data *data)
{
	init_mlx(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx, data->win_width, data->win_height
		, "cub");
	if (!data->win_ptr)
		return (1);
	data->image.img = mlx_new_image(data->win_ptr, data->win_width
		, data->win_height);
	if (!data->image.img)
		return (1); // Return error if image creation fail
	data->image.addr = mlx_get_data_addr(data->image.img
		,&data->image.bits_per_pixel, &data->image.line_length
		, &data->image.endian);
	if (!data->image.addr)
		return (1);
	init_sprite(data);
	if (load_textures(data) || load_sprite(data))
		return (1);
		
	mlx_mouse_hook(data->win_ptr, pres_mousse, data);
	mlx_hook(data->win_ptr, 2, (1L<<0), pres_bouton, data);
	mlx_hook(data->win_ptr, 3, (1L<<1), release_bouton, data);
	mlx_hook(data->win_ptr, 17, 0L, clear_all, data);
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


void	init_game(t_data *data)
{
	data->mini_map_height = 400;
	data->mini_map_width = 400;
	data->mini_tile_size = 20;
	data->win_width = 1700;
	data->win_height = 1350;
	data->tile_size = 64;
	data->map_height = data->carte.row * data->tile_size;
	data->map_width = data->carte.col * data->tile_size;
	data->fov_angle = 60 * M_PI / 180;
	data->player = my_malloc(sizeof (t_player), 0);
	data->player->player_coor.x = data->tile_size * data->carte.player.x
		+ data->tile_size / 2;
	data->player->player_coor.y = data->tile_size * data->carte.player.y
		+ data->tile_size / 2;
	data->player->player_rotation = init_player_rotation(data);
	data->nbr_rays = data->win_width;
	data->rays = my_malloc(sizeof (t_ray) * data->nbr_rays, 0);
	if (!data->player)
		return ((void)clear_all(data));
	send_rays(data);
}
void	f()
{system("leaks cub");}
int	main(int ac, char **av)
{
	t_data	data;

	// atexit(f);
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
/*
./cub3d maps/good/square_map.cub 
*/