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
		data->player->player_rotation = angle_normalize(data->player->player_rotation 
			+ MOUSSE_SENSITIVITY * delta_y);
		send_rays(data);
		render_game(data);
	}
	y_mousse = y;
	(void)x;
	return (0);
}
