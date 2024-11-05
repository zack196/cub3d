#include "cub3d.h"

int is_player(char player_direction, t_player *player)
{
	if (player_direction == 'N')
	{
		player->rotation_angle = 3 * M_PI_2;
		return (1);
	}
	else if (player_direction == 'S')
	{
		player->rotation_angle = M_PI_2;
		return (1);
	}
	else if (player_direction == 'E')
	{
		player->rotation_angle = 0;
		return (1);
	}
	else if (player_direction == 'W')
	{
		player->rotation_angle = M_PI;
		return (1);
	}
	return (0);
}

void    player_init(t_cub *cub)
{
	int		i_map;
	int		j_map;
	char	**map;

	cub->player = my_malloc(sizeof (t_player), 0);
	map = cub->map;
	i_map = -1;
	while (map[++i_map])
	{
		j_map = 0;
		while (map[i_map][j_map])
		{
			if (is_player(map[i_map][j_map], cub->player))
				break ;
			j_map++;
		}
		if (is_player(map[i_map][j_map], cub->player))
			break ;
	}
	cub->player->x_player = cub->tile_size * i_map + cub->tile_size / 2;
	cub->player->y_player = cub->tile_size * j_map + cub->tile_size / 2;
}

void	update_player(t_cub *cub, int walk, int turn, int rotation)
{
	t_player	*player;
	float		x_new_pos;
	float		y_new_pos;

	x_new_pos = 0;
	y_new_pos = 0;
	player = cub->player;
	x_new_pos = player->x_player + walk * 10 * MAP_SCALE * sin(player->rotation_angle)
		- turn * 10 * MAP_SCALE * cos(player->rotation_angle);
	y_new_pos = player->y_player + walk * 10 * MAP_SCALE * cos(player->rotation_angle)
		+ turn * 10 * MAP_SCALE * sin(player->rotation_angle);
	player->rotation_angle = angle_normalize(((9 * M_PI / 180) * rotation)
		+ player->rotation_angle);
	if (!is_wall(cub, (int)x_new_pos, (int)y_new_pos))
	{
		player->x_player = (int)x_new_pos;
		player->y_player = (int)y_new_pos;
	}
}

