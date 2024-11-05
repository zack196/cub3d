#include "cub3d.h"

int	pres_bouton(int keycode, t_cub *cub)
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
	update_player(cub, walk, turn, rotation);
	send_rays(cub);
	render_walls(cub);
	render_map(cub);
	render_player(cub);
    render_rays(cub);
	return (0);
}

int release_bouton(int keycode, t_cub *cub)
{
	(void)keycode;
	render_walls(cub);
	render_map(cub);
	render_player(cub);
    render_rays(cub);
	return (0);
}