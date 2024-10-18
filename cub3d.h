#ifndef CUB3D
#define CUB3D 2

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

#define TILE_SIZE 100
#define WIDTH TILE_SIZE * 15
#define HEIGHT TILE_SIZE * 5

typedef struct s_g_data
{
    void			*data;
    struct s_g_data	*next;
}   t_g_data;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*mlx;
	void	*win_mlx;
	t_image	image;
}	t_mlx;


typedef struct s_player
{
	int		player_x;
	int		player_y;

}	t_player;

typedef struct s_cub
{
    char		**map;
	char		**mini_map;
	int			map_height;
	int			map_width;
	t_player	*player;

	void	*mlx;
	void	*win_mlx;
	t_image	image;

}   t_cub;


void	*my_malloc(size_t size, int free_mode);
char	*ft_strdup(char *str);
int 	ft_strlen(char *str);
void	get_player_position(t_cub *cub);
int		mlx_handel(t_cub *cub);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
int		check_player(char c);
int		key_pres(int button, t_cub *cub);
void	render_cub(t_cub *cub);

//tmp
char    **generate_map();
#endif