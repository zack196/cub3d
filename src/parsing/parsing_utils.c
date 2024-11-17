/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:59:27 by hel-band          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/17 16:30:22 by zel-oirg         ###   ########.fr       */
=======
/*   Updated: 2024/11/17 16:23:23 by hel-band         ###   ########.fr       */
>>>>>>> 7ca3eb740325d93a0c35c2e7722fcc9924235d3a
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	ft_spl_free(char **spl)
// {
// 	int	i;

// 	i = 0;
// 	while (spl[i])
// 		free(spl[i++]);
// 	free(spl);
// }

int	ft_len_map(t_data  *data)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (data->map[i])
	{
		char *line = ft_strtrim(data->map[i], " ");
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