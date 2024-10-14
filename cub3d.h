#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 99
#endif

#define TILE_SIZE 32

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_gdata
{
    void			*data;
    struct s_gdata	*next;
}	t_gdata;

typedef struct s_cub
{
    char	*texture_no;
    char	*texture_so;
    char	*texture_we;
    char	*texture_ea;
    char	**maps;

    int		F_COLOR;
    int		C_COLOR;


	void	*mlx;
	void	*mlx_win;
	t_data	img;

}	t_cub;

void	*my_malloc(size_t size, int free_mode);
int		parce_cub(t_cub *cub, char *file_name);
char	*gnl(int fd);
void	my_free(void);
int ft_strlen(char *str);
char	*ft_strdup(char *str);
#endif