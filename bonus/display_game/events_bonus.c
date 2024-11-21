/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:52:10 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/21 22:02:19 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	check_player_move(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	facteur;

	facteur = 8;
	i = x - facteur;
	while (++i < x + facteur)
	{
		j = y - facteur;
		while (++j < y + facteur)
			if (is_wall(data, i, j) || is_door(data, x, y))
				return (0);
	}
	return (1);
}

void	update_player(t_data *data, int walk, int turn, int rotation)
{
	t_player	*player;
	float		x_new_pos;
	float		y_new_pos;

	x_new_pos = 0;
	y_new_pos = 0;
	player = data->player;
	x_new_pos = player->player_coor.x + walk * sin(player->player_rotation)
		+ turn * cos(player->player_rotation);
	y_new_pos = player->player_coor.y + walk * cos(player->player_rotation)
		- turn * sin(player->player_rotation);
	player->player_rotation = angle_normalize(((1 * M_PI / 180) * rotation)
			+ player->player_rotation);
	if (check_player_move(data, x_new_pos, y_new_pos))
	{
		player->player_coor.x = (int)x_new_pos;
		player->player_coor.y = (int)y_new_pos;
	}
}

void	get_button(int keycode, int *walk, int *turn, int *rotation)
{
	if (keycode == 0)
		*turn = -STEP;
	else if (keycode == 1)
		*walk = -STEP;
	else if (keycode == 2)
		*turn = STEP;
	else if (keycode == 13)
		*walk = STEP;
	else if (keycode == 123)
		*rotation = -ROTATION_STEP;
	else if (keycode == 124)
		*rotation = ROTATION_STEP;
}

int	pres_bouton(int keycode, t_data *data)
{
	int	walk;
	int	turn;
	int	rotation;

	walk = 0;
	rotation = 0;
	turn = 0;
	get_button(keycode, &walk, &turn, &rotation);
	if (keycode == 53)
		clear_all(data);
	else if (keycode == 49)
		data->open_door = !data->open_door;
	if (keycode == 46)
		data->mouse_active = !data->mouse_active;
	update_player(data, walk, turn, rotation);
	send_rays(data);
	render_game(data);
	return (0);
}

int	release_bouton(int keycode, t_data *data)
{
	(void)keycode;
	data->sprite.stop_animation = 1;
	render_game(data);
	return (0);
}
