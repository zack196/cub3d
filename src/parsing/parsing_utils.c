/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:59:27 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/25 16:27:16 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_len_map(t_data *data)
{
	int		i;
	int		size;
	char	*line;

	i = 0;
	size = 0;
	while (data->map[i])
	{
		line = ft_strtrim(data->map[i], " ");
		if (line[0] == '1' || line[0] == '0')
		{
			size++;
		}
		i++;
	}
	return (size);
}

int	ft_find_newline(char *str)
{
	return (str[ft_strlen(str) - 1] == '\n');
}

int	ft_find_char(char x, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (x == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_find_player_pos(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (map->cub[row])
	{
		col = 0;
		while (map->cub[row][col])
		{
			if (ft_find_char(map->cub[row][col], "NSEW"))
			{
				map->player.x = row;
				map->player.y = col;
				map->starting_derection = map->cub[row][col];
			}
			col++;
		}
		row++;
	}
}
