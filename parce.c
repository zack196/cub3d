#include "cub3d.h"

char	*get_texture(int fd, char *direction)
{
	char	*line;

	line = gnl(fd);
	while (*line == '\n')
		line = gnl(fd);
	if (!line)
		return (NULL);
	while (*line == ' ')
		line++;
	if (line[0] != direction[0] || line[1] != direction[1])
		return (NULL);
	line++;
	line++;
	while (*line == ' ')
		line++;
	return (line);
}

int	color_to_int(char *color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while ('0' <= color[i] && color[i] <= '9' && r < 256 && color[i] != ',')
		r = r * 10 + (color[i++] - '0');
	if (color[i] != ',' && r >= 256)
		return (-1);
	while ('0' <= color[i] && color[i] <= '9' && r < 256 && color[i] != ',')
		g = g * 10 + (color[i++] - '0');
	if (color[i] != ',' && g >= 256)
		return (-1);
	while ('0' <= color[i] && color[i] <= '9' && r < 256 && color[i] != ',')
		b = b * 10 + (color[i++] - '0');
	if (color[i] != ',' && r >= 256)
		return (-1);
	return ((r << 16) + (g << 8) + b);
}

int	get_color(char color, int fd)
{
	char	*line;
	int		ret_color;

	line = gnl(fd);
	if (*line == '\n')
		line = gnl(fd);
	while (*line == ' ')
		line++;
	if (*line != color)
		return (-1);
	line++;
	while (*line == ' ')
		line++;
	ret_color = color_to_int(line);
	return(ret_color);
}

char	**append_line(char **map, char *line)
{
	int		i;
	char	**res;

	i = 0;
	if (!line)
		return (map);
	while (map && map[i])
		i++;
	res = my_malloc((i + 2) * sizeof (char *), 0);
	i = 0;
	while (map && map[i])
	{
		res[i] = map[i];
		i++;
	}
	res[i++] = line;
	res[i] = NULL;
	return (res);
}

char	**get_maps(int fd)
{
	char	**map;
	char	*line;

	line = gnl(fd);
	while (*line == '\n')
		line = gnl(fd);
	map = NULL;
	map = append_line(map, line);
	while (line)
	{
		line = gnl(fd);
		map = append_line(map, line);
	}
	return (map);
}
void	fct(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->maps[++i])
	{
		j = -1;
		while (cub->maps[i][++j])
			if (cub->maps[i][j] == 'N' || cub->maps[i][j] == 'S'
				|| cub->maps[i][j] == 'W' || cub->maps[i][j] == 'E')
				;
	}
}

int	parce_cub(t_cub *cub, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	cub->texture_no = get_texture(fd, "NO");
	cub->texture_so = get_texture(fd, "SO");
	cub->texture_we = get_texture(fd, "WE");
	cub->texture_ea = get_texture(fd, "EA");
	cub->F_COLOR = get_color('F', fd);
	cub->F_COLOR = get_color('C', fd);
	cub->maps = get_maps(fd);
	close(fd);
	if (!cub->texture_no || !cub->texture_so || !cub->texture_we
		|| !cub->texture_ea || cub->C_COLOR == -1 || cub->F_COLOR == -1)
		return (1);
	
	
	return (0);
}
