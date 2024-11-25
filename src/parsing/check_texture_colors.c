/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:13:29 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/25 16:08:23 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_process_texture_line(t_data *data, int *ptr,
		int *flag, int *color)
{
	char	*line;

	line = ft_strtrim(data->map[*ptr], " ");
	if (!line)
		print_error("", "Error trimming line", 1);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		(*flag)++;
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		(*color)++;
}

static void	ft_pars_texture(t_data *data, int *ptr)
{
	int	flag;
	int	color;

	flag = 0;
	color = 0;
	while (data->map[*ptr])
	{
		while (data->map[*ptr] && ft_strtrim(data->map[*ptr], " \t") == NULL)
			(*ptr)++;
		if (!data->map[*ptr])
			break ;
		if (data->map[*ptr][0] == '1' || data->map[*ptr][0] == '0')
			break ;
		ft_process_texture_line(data, ptr, &flag, &color);
		(*ptr)++;
	}
	if (flag != 4)
		print_error("", "Error in textures ", 1);
	if (color != 2)
		print_error("", "Error in  colors", 1);
	if (*ptr == 0)
		print_error("", "Empty map", 1);
}

void	ft_find_content(t_data *data)
{
	int	i;

	i = 0;
	ft_pars_texture(data, &i);
	while (data->map[i] && ft_strtrim(data->map[i], " \t") == NULL)
		i++;
	if (data->map[i] == NULL)
		print_error("", "No map included", 1);
}
