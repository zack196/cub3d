/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:40 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/11/21 21:53:27 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	begin_animation(t_data *data)
{
	data->sprite.frame_delay = 100;
	data->sprite.curent_frame = 0;
	data->sprite.stop_animation = 0;
	data->sprite.last_render = now();
}

void	init_sprite(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NBR_FRAME)
	{
		data->sprite.frame[i].tex_name = ft_strjoin("sprite/",
				ft_strjoin(ft_itoa(i), ".xpm"));
		data->sprite.frame[i].addr = NULL;
		data->sprite.frame[i].img = NULL;
	}
}

int	load_sprite(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NBR_FRAME)
	{
		data->sprite.frame[i].img = mlx_xpm_file_to_image(data->mlx,
				data->sprite.frame[i].tex_name, &data->sprite.frame[i].width,
				&data->sprite.frame[i].height);
		if (!data->sprite.frame[i].img)
			return (1);
		data->sprite.frame[i].addr
			= mlx_get_data_addr(data->sprite.frame[i].img,
				&data->sprite.frame[i].bits_per_pixel,
				&data->sprite.frame[i].line_length,
				&data->sprite.frame[i].endian);
		if (!data->sprite.frame[i].addr)
			return (1);
	}
	data->sprite.x = data->win_width / 2 - data->sprite.frame->width / 2;
	data->sprite.y = data->win_height - data->sprite.frame->height;
	return (0);
}

int	render_sprite_animation(t_data *data)
{
	t_sprite	*sprite;
	long		delta_t;
	long		time_now;

	sprite = &data->sprite;
	time_now = now();
	delta_t = time_now - sprite->last_render;
	if (delta_t > sprite->frame_delay)
	{
		if (sprite->stop_animation)
			return (0);
		mlx_clear_window(data->mlx, data->win_ptr);
		render_walls(data);
		mini_map(data);
		mlx_put_image_to_window(data->mlx, data->win_ptr, data->image.img, 0,
			0);
		mlx_put_image_to_window(data->mlx, data->win_ptr,
			data->sprite.frame[sprite->curent_frame].img, data->sprite.x,
			data->sprite.y);
		sprite->curent_frame++;
		if (sprite->curent_frame >= NBR_FRAME)
			(1) && (sprite->stop_animation = 1, sprite->curent_frame = 0);
		sprite->last_render = time_now;
	}
	return (0);
}
