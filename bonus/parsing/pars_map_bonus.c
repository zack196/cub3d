/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:17:53 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/27 07:58:05 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	ft_get_number_line(char *av)
{
	char	*line;
	int		fd;
	int		number_lines;

	number_lines = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		print_error(av, "fd get_line_map:", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		number_lines++;
		line = get_next_line(fd);
	}
	close(fd);
	return (number_lines);
}

static void	ft_remplir_map(t_data *data)
{
	int	fd;
	int	i;

	fd = open(data->carte.filename, O_RDONLY);
	if (fd == -1)
		print_error("", "fd ft_remplir_map:", 1);
	data->map = ft_calloc(data->carte.nbr_line + 1, sizeof(char *));
	if (!data->map)
		print_error("", "Memory allocation failed for map", 1);
	i = 0;
	data->map[i] = get_next_line(fd);
	while (i < data->carte.nbr_line && data->map[i++])
		data->map[i] = get_next_line(fd);
	data->map[i] = NULL;
	close(fd);
}

void	ft_pars_map(t_data *data)
{
	int	fd;

	fd = open(data->carte.filename, O_RDONLY);
	if (fd == -1)
		print_error(data->carte.filename, "cannot open file:", 1);
	data->carte.nbr_line = ft_get_number_line(data->carte.filename);
	if (data->carte.nbr_line == 0)
		print_error(data->carte.filename, "nbr_line_in_map_invalid:", 1);
	close(fd);
	ft_remplir_map(data);
}
