#include "../../include/cub3d.h"

void	update_player(t_data *data, int walk, int turn, int rotation)
{
	t_player	*player;
	float		x_new_pos;
	float		y_new_pos;

	x_new_pos = 0;
	y_new_pos = 0;
	player = data->player;
	x_new_pos = player->player_coor.x + walk * 7 * MAP_SCALE
        * sin(player->player_rotation)
		+ turn * 7 * MAP_SCALE * cos(player->player_rotation);
	y_new_pos = player->player_coor.y + walk * 7 * MAP_SCALE
        * cos(player->player_rotation)
		- turn * 7 * MAP_SCALE * sin(player->player_rotation);
	player->player_rotation = angle_normalize(((5 * M_PI / 180) * rotation)
		+ player->player_rotation);
	if (!is_wall(data, (int)x_new_pos, (int)y_new_pos))
	{
		player->player_coor.x = (int)x_new_pos;
		player->player_coor.y = (int)y_new_pos;
	}
}

int	pres_bouton(int keycode, t_data *data)
{
    int	walk;
	int	turn;
	int	rotation;

	walk = 0;
	rotation = 0;
	turn = 0;
	if (keycode == 0)//97 //a
		turn = -1;
	else if (keycode == 1)// 115 //s
		walk = -1;
	else if (keycode == 2)// 100 //d
		turn = 1;
	else if (keycode == 13)// 119 //w
		walk = 1;
	else if (keycode == 123)// 65361   //<<
		rotation -= 1;
	else if (keycode == 124)// 65363   //>>
		rotation -= -1;
	update_player(data, walk, turn, rotation);
	send_rays(data);
	render_game(data);
	return (0);
}

int release_bouton(int keycode, t_data *data)
{
	(void)keycode;
	render_game(data);
	return (0);
}