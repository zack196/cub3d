/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:20:18 by hel-band          #+#    #+#             */
/*   Updated: 2024/12/03 13:41:05 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_find_cub_(char *src, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(src) - ft_strlen(to_find);
	while ((src[j] && to_find[i]) && (src[j++] == to_find[i++]))
		;
	if (j == ft_strlen(src))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	print_error(char *arg, char *str, int fd)
{
	ft_putstr_fd("Cub3D: Error", 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(fd);
}

static int	ft_derctory(char *arg)
{
	int	fd;

	fd = open(arg, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	ft_find_cub(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b' || arg[len - 4] != '.'))
		return (1);
	return (0);
}

int	ft_pars_file(char *arg)
{
	int	fd;

	if (ft_derctory(arg) == 1)
		print_error(arg, "Is a directory\n", 1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		print_error(arg, "fd pars_file:", 1);
	close(fd);
	if (ft_find_cub(arg) == 0)
		print_error("", "you should have a cube file", 1);
	return (1);
}
