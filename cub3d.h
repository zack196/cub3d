#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include <stdlib.h>

# define MAP_SCALE 0.3
# define HEIGHT 800
# define WIDTH 1600
# define FOV_ANGLE M_PI / 3

# define WALL_STRIP_WIDTH 1 // ta tchof had lblan
# define NBR_RAYS WIDTH / WALL_STRIP_WIDTH


typedef struct s_gdata
{
    void			*data;
    struct s_gdata	*next;
}   t_gdata;

void	*my_malloc(size_t size, int free_mode);
void	my_free(void);

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_player
{
    int     x_player;
    int     y_player;
    float   rotation_angle;


}   t_player;

typedef struct s_ray
{
    int     ray_facing_up;
    int     ray_facing_right;
    
    float   angle;
    float   distance;
}   t_ray;

typedef struct s_cub
{
    //map parametres
    char		**map;
    int			map_width;
    int			map_height;
    int         floor_color;
    int         ceiling_color;
    //mini map
    int			tile_size;
    int			map_window_width;
    int			map_window_height;

    //mlx
    void		*mlx;
    void		*mlx_win;
    t_data		image;

    t_player	*player;
    t_ray       *rays;


}   t_cub;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);

//game initialisation
void	sizing_map(t_cub *cub);
void    player_init(t_cub *cub);

//mlx
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//render
void    render_map(t_cub *cub);
void	render_player(t_cub *cub);
void    render_walls(t_cub *cub);

//mlx event
int pres_bouton(int keycode, t_cub *cub);
int release_bouton(int keycode, t_cub *cub);

//rays
void    send_rays(t_cub *cub);
void	render_rays(t_cub *cub);


//utile
int     is_wall(t_cub *cub, int x, int y);
float   angle_normalize(float angle);
void	update_player(t_cub *cub, int walk, int turn, int rotation);

//tmp
char	**tmp_map(t_cub *cub);
void draw_line(t_data *img, int x_origin, int y_origin, int x_end, int y_end, int color);
#endif