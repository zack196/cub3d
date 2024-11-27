/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:15:36 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 08:20:40 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>

# define NBR_FRAME 75
# define EQUAL 0

//****COLORS
# define RESET	"\e[0m"
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define FLOOR "F"
# define CEILLING "C"

# define NORTH_TEXTURE "NO"
# define SOUTH_TEXTURE "SO"
# define EAST_TEXTURE "EA"
# define WEST_TEXTURE "WE"

# define MAP_SCALE 1.7
# define STEP 15
# define ROTATION_STEP 10
# define MOUSSE_SENSITIVITY 0.006

typedef struct s_gdata
{
	void			*data;
	struct s_gdata	*next;
}	t_gdata;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_float_vector
{
	float	x;
	float	y;
}	t_float_vector;

typedef struct s_map
{
	int			row;
	int			col;
	int			nbr_line;
	char		**file;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_color		floor_color;
	t_color		ceilling_color;
	char		starting_derection;
	int			index_end_of_map;
	char		**cub;
	char		*filename;
	t_vector	player;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_player
{
	float		player_rotation;
	t_vector	player_coor;
	t_vector	player_map;
}	t_player;

typedef struct s_ray
{
	float			angle;
	float			distance;
	int				ray_facing_right;
	int				ray_facing_up;
	int				is_hit_vertical;
	int				is_door;
	t_float_vector	hit_coord;
}	t_ray;

typedef struct s_texture
{
	char	*tex_name;
	char	*addr;
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_sprite
{
	t_texture	frame[NBR_FRAME];
	long		last_render;
	long		frame_delay;
	int			x;
	int			y;
	int			curent_frame;
	int			stop_animation;
}	t_sprite;

typedef struct s_data
{
	void			*mlx;
	void			*win_ptr;
	t_image			image;
	t_texture		textures[5];
	t_texture		door;
	int				open_door;
	int				ac;
	char			**av;
	int				win_height;
	int				win_width;
	int				map_height;
	int				map_width;
	int				tile_size;
	t_map			carte;
	char			**map;
	t_player		*player;
	int				nbr_rays;
	t_ray			*rays;
	float			fov_angle;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int				mini_map_height;
	int				mini_map_width;
	int				mini_tile_size;
	t_sprite		sprite;
	int				mouse_active;
}	t_data;

int				main(int ac, char **av);
int				print_error(char *arg, char *str, int fd);
int				ft_pars_file(char *arg);
void			ft_pars_map(t_data *data);
void			ft_find_content(t_data *data);
void			ft_add_textures(t_data *data);
void			ft_add_colors(t_data *data);
int				ft_len_map(t_data *data);
int				ft_find_newline(char *str);
int				ft_find_char(char x, char *str);
void			ft_find_player_pos(t_map *map);
int				ft_pars_wall(char **cub, int row);
int				ft_surrond_wall(char **cub, int row, int col);
int				ft_check_wall(char **cub, int row, int col);
void			ft_last_pars_cub(t_map map);
void			ft_check_cub(t_map map, int row, int col);
void			ft_take_cub(t_data *data);
void			ft_pars_cub(char **cub, t_data *data);
void			ft_init_game(t_data *data);
void			ft_init_carte(t_map *map);
void			init_color(t_color *color);
int				ft_find_cub_(char *src, char *to_find);

int				pres_bouton(int keycode, t_data *cub);
int				release_bouton(int keycode, t_data *cub);

void			render_walls(t_data *data);
void			render_game(t_data *data);

float			angle_normalize(float angle);
int				is_wall(t_data *data, int x, int y);
float			init_player_rotation(t_data *data);
void			draw_line(t_image *img, t_vector origine,
					t_vector end, int color);
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
float			distance(t_vector a, t_float_vector b);
int				mini_wall(t_data *data, int x, int y, int tile_size);

void			send_rays(t_data *data);

long			now(void);
int				clear_all(t_data *data);
void			render_map(t_data *data);

int				load_textures(t_data *data);
void			textured_wall(t_data *data, int x, int y, float wall_height);

void			mini_map(t_data *data);
int				load_sprite(t_data *data);
int				get_texture_color(t_texture *tex, int tex_x, int tex_y);
void			init_sprite(t_data *data);
int				pres_mousse(int button, int x, int y, t_data *data);
void			mousse_render(t_data *data, int frame);

int				render_sprite_animation(t_data *data);
void			begin_animation(t_data *data);
int				is_door(t_data *data, int x, int y);
int				mouse_move_hook(int x, int y, t_data *data);

t_float_vector	horizontal_wall_hit_distace(t_ray *ray, t_data *data);
t_float_vector	vertical_wall_hit_distance(t_ray *ray, t_data *data);
float			distance(t_vector a, t_float_vector b);
void			ray_facing(t_ray *ray);
void			get_rays_values(t_data *data, t_ray *ray,
					t_float_vector vert, t_float_vector horz);
void			init_game(t_data *data);
void			init_mlx(t_data *data);
#endif
