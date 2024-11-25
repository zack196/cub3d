/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:11:11 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/25 17:13:13 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_add_textures(t_data *data)
{
	char	**texter;
	int		i;

	i = 0;
	while (data->map[i])
	{
		texter = ft_split(data->map[i++], ", \n");
		if (texter[0] && (ft_strcmp(texter[0], NORTH_TEXTURE) == 0))
			data->carte.north_texture = ft_strdup(texter[1]);
		else if (texter[0] && (ft_strcmp(texter[0], SOUTH_TEXTURE) == 0))
			data->carte.south_texture = ft_strdup(texter[1]);
		else if (texter[0] && (ft_strcmp(texter[0], WEST_TEXTURE) == 0))
			data->carte.west_texture = ft_strdup(texter[1]);
		else if (texter[0] && (ft_strcmp(texter[0], EAST_TEXTURE) == 0))
			data->carte.east_texture = ft_strdup(texter[1]);
	}
	if (open(data->carte.north_texture, O_RDONLY) < 0
		|| open(data->carte.south_texture, O_RDONLY) < 0
		|| open(data->carte.east_texture, O_RDONLY) < 0
		|| open(data->carte.west_texture, O_RDONLY) < 0)
		print_error("", "Error in open textures", 1);
}

static unsigned int	ft_type_colors(char **colors)
{
	int		red;
	int		green;
	int		blue;

	if (colors[0] && colors[1] && colors[2] && colors[3] == NULL)
	{
		red = ft_atoi(colors[0]);
		green = ft_atoi(colors[1]);
		blue = ft_atoi(colors[2]);
		if ((red >= 0 && red <= 255) && (green >= 0 && green <= 255)
			&& (blue >= 0 && blue <= 255))
			return ((unsigned int)(red << 16) | (unsigned int)(green << 8)
				| (unsigned int)blue);
		else
			print_error("", "RGB values out of range (0-255)", 1);
	}
	else
		print_error("", "Problem in colors: invalid format", 1);
	return (0);
}

void	ft_add_colors(t_data *data)
{
	char			**colors;
	int				i;

	i = 0;
	while (data->map[i])
	{
		if (data->map[i][0] == '1' || data->map[i][0] == ' '
			|| data->map[i][0] == '0')
			break ;
		colors = ft_split(data->map[i], ", \n");
		if (colors[0])
		{
			if (ft_strcmp(colors[0], FLOOR) == 0)
			{
				data->floor_color = ft_type_colors(colors + 1);
			}
			else if (ft_strcmp(colors[0], CEILLING) == 0)
			{
				data->ceiling_color = ft_type_colors(colors + 1);
			}
		}
		i++;
	}
}

static void	ft_process_line(t_data *data, char *line, int *j)
{
	if (line[0] == '1' || line[0] == '0')
	{
		data->carte.cub[*j] = ft_strndup(line,
				ft_strlen(line) - ft_find_newline(line));
		if (data->carte.col < (int)ft_strlen(data->carte.cub[*j]))
			data->carte.col = ft_strlen(data->carte.cub[*j]);
		(*j)++;
	}
}

void	ft_take_cub(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	data->carte.row = ft_len_map(data);
	data->carte.cub = my_malloc(sizeof(char *) * (data->carte.row + 1), 0);
	if (!data->carte.cub)
		print_error("", "Error in malloc in take_cub", 1);
	data->carte.col = 0;
	while (data->map[i])
	{
		if (data->map[i][0] == ' ')
		{
			line = ft_strtrim(data->map[i], " ");
			ft_process_line(data, line, &j);
		}
		if (data->map[i][0] == '1' || data->map[i][0] == '0')
			ft_process_line(data, data->map[i], &j);
		i++;
	}
	data->carte.cub[j] = 0;
}
