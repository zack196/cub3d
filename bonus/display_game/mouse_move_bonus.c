/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:51:42 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/21 22:00:22 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	mouse_move_hook(int y, int x, t_data *data)
{
	static int	y_mousse = -1;
	float		delta_y;

	if (!data->mouse_active)
		return (0);
	if (y_mousse != -1)
	{
		delta_y = (float)(y - y_mousse);
		data->player->player_rotation
			= angle_normalize(data->player->player_rotation + MOUSSE_SENSITIVITY
				* delta_y);
		send_rays(data);
		render_game(data);
	}
	y_mousse = y;
	(void)x;
	return (0);
}

int	pres_mousse(int button, int y, int x, t_data *data)
{
	if (button == 1)
	{
		begin_animation(data);
		mlx_loop_hook(data->mlx, render_sprite_animation, data);
	}
	(void)x;
	(void)y;
	return (0);
}
