/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:15:36 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/06 11:22:19 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <unistd.h>

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

# define MAP_SCALE 0.2
# define HEIGHT 720
# define WIDTH 1280

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

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_player
{
	float		player_rotation;
	t_vector	player_coor;
}	t_player;

typedef struct s_ray
{
	float	angle;
	float	distance;
	int		ray_facing_right;
	int		ray_facing_up;
}	t_ray;

typedef struct s_data
{
	//mlx
	void		*mlx;
	void		*win_ptr;
	t_image		image;
	
    int         ac;
    char        **av;
	int			win_height;
	int			win_width;
	//mini_map
	int			mini_map_window_height;
	int			mini_map_window_width;
	int			tile_size;
	
	t_map	    carte;
	char		**map;
	//player data
	t_player	*player;

	//rays data
	int			nbr_rays;
	t_ray		*rays;
	float		fov_angle;
	
}	t_data;

// *** parsing ***:
int main(int ac, char **av);
int		print_error(char *arg, char *str, int fd);
int		ft_pars_file(char *arg);
void	ft_pars_map(t_data *data);
void	ft_find_content(t_data *data);
void	ft_spl_free(char **spl);
void    ft_add_textures(t_data *data);
void    ft_add_colors(t_data *data);
int		ft_len_map(t_data  *data);
int		ft_find_newline(char *str);
int		ft_find_char(char x, char *str);
void    ft_find_player_pos(t_map *map);
int ft_pars_wall(char **cub, int row);
int ft_surrond_wall(char **cub, int row, int col);
int	ft_check_wall(char **cub, int row, int col);
void    ft_last_pars_cub(t_map map);
void	ft_check_cub(t_map map, int row, int col);
void	ft_take_cub(t_data *data);
void    ft_pars_cub(char **cub ,t_data *data);
void	ft_init_game(t_data *data);
void	ft_init_carte(t_map *map);
void	init_color(t_color *color);
int	ft_find_cub_(char *src, char *to_find);

//mlx event
int pres_bouton(int keycode, t_data *cub);
int release_bouton(int keycode, t_data *cub);

//redring 
// void    render_game(t_data *data);
int    render_game(t_data *data);
//utiles
float   angle_normalize(float angle);
int 	is_wall(t_data *data, int x, int y);
float	init_player_rotation(t_data *data);
void 	draw_line(t_image *img, t_vector origine, t_vector end, int color);
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
//rays
void    send_rays(t_data *data);




void	render_map(t_data *data);
#endif