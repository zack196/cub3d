#include "cub3d.h"

int	x_mini_map(t_cub *cub)
{
	int	x;

	get_player_position(cub);
	if (cub->player->player_x > 2)
		x = cub->player->player_x - 2;
	else 
		x = 0;
	if (cub->player->player_x + 3 > cub->map_height)
	{
		if (cub->map_height - 5 > 0)
			x = cub->map_height - 5;
		else
			x = 0;
	}
	return (x);
}

int	y_mini_map(t_cub *cub)
{
	int	y;

	get_player_position(cub);
	if (cub->player->player_y > 7)
		y = cub->player->player_y - 7;
	else
		y = 0;
	if (cub->player->player_y + 8 > cub->map_width)
	{
		if (cub->map_width - 15 > 0)
			y = cub->map_width - 15;
		else
			y = 0;
	}
	return (y);
}

char	**get_mini_map(t_cub *cub)
{
	char	**mini_map;
	int		x;
	int		y;
	int		i;
	int		j;

	get_player_position(cub);
	x = x_mini_map(cub);
	y = y_mini_map(cub);
	mini_map = my_malloc(sizeof (char *) * 6, 0);
	i = -1;
	while (++i < 5 && cub->map[i + x])
	{
		mini_map[i] = my_malloc(sizeof (char) * 16, 0);
		j = -1;
		while (++j < 15 && cub->map[i + x][j + y])
			mini_map[i][j] = cub->map[i + x][j + y];
		mini_map[i][j] = '\0';
	}
	mini_map[i] = NULL;
	return (mini_map);
}

void	display_player(t_cub *cub, int i, int j)
{
	int x_center;
	int y_center;
	int radius;

	// Calculate the player's center in pixel coordinates
	x_center = cub->player->player_x * TILE_SIZE + TILE_SIZE / 2;
	y_center = cub->player->player_y * TILE_SIZE + TILE_SIZE / 2;

	// Set the radius for the player's circle
	radius = TILE_SIZE / 3;  // Adjust the size of the circle as needed

	// Check if the current pixel is inside the player's circle using the equation (x - center_x)^2 + (y - center_y)^2 < radius^2
	if ((i - x_center) * (i - x_center) + (j - y_center) * (j - y_center) < radius * radius)
	{
		my_mlx_pixel_put(&cub->image, j, i, 0XFFFFFF);  // Player color (white)
	}
}

void	coloring_pixel(t_cub *cub, char **mini_map, int i, int j)
{
	int		x_mini_map;
	int		y_mini_map;

	// Get the tile position in the minimap
	x_mini_map = i / TILE_SIZE;
	y_mini_map = j / TILE_SIZE;

	// Ensure we're within the minimap bounds
	if (x_mini_map < 5 && y_mini_map < 15 && mini_map[x_mini_map])
	{
		// Draw based on the tile type
		if (mini_map[x_mini_map][y_mini_map] == '0')       // Empty space
			my_mlx_pixel_put(&cub->image, j, i, 0X05EA22); // Green for space
		else if (mini_map[x_mini_map][y_mini_map] == '1')  // Wall
			my_mlx_pixel_put(&cub->image, j, i, 0X253A62); // Dark blue for wall
		else if (check_player(mini_map[x_mini_map][y_mini_map])) // Player
		{
			// Display the player on the minimap
			display_player(cub, i, j);
		}
	}
}

void	render_cub(t_cub *cub)
{
	char	**mini_map;
	int		i;
	int		j;

	// Get the current minimap section to display
	mini_map = get_mini_map(cub);

	// Loop through the window pixels
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			coloring_pixel(cub, mini_map, i, j); // Color each pixel
	}

	// Display the image on the window
	mlx_put_image_to_window(cub->mlx, cub->win_mlx, cub->image.img, 0, 0);
}


void	sizing_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map_width = 0;
	while (cub->map[i])
	{
		if (cub->map_width < ft_strlen(cub->map[i]))
			cub->map_width = ft_strlen(cub->map[i]);
		i++;
	}
	cub->map_height = i;
}

int	main()
{
	t_cub	cub;

	cub.map = generate_map();
	sizing_map(&cub);
	cub.player = my_malloc(sizeof (t_player), 0);
	if (mlx_handel(&cub))
		return (my_malloc(1, 1), 1);
	render_cub(&cub);
	mlx_loop(cub.mlx);
	my_malloc(0, 1);
	return (0);
}
