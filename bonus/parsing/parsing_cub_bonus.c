/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:56:16 by hel-band          #+#    #+#             */
/*   Updated: 2024/11/20 04:10:17 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int ft_arroud_player(char **cub, int row, int col ,t_data *data)
{
    row = data->carte.player.x;
    col = data->carte.player.y;
   if (col <= 0 || col >= data->carte.col || row <= 0 || row >= data->carte.row)
        print_error("", "Player is too close to map boundary", 1);
    if (cub[row][col + 1] == ' ' || cub[row][col - 1] == ' '
        || cub[row + 1][col] == ' ' || cub[row - 1][col] == ' ')
        print_error("", "Player surrounded by spaces", 1);
    return (1);
}
void    ft_pars_cub(char **cub ,t_data *data)
{
    int i;
    int j;
    int flag;

    flag = 0;
    i = 0;
    while (cub[i])
    {
        j = 0;
        while (cub[i][j])
        {
            if (!ft_find_char(cub[i][j], " 01NSEWD"))
                print_error("", "Invalid charachter in map", 1);
            if (ft_find_char(cub[i][j], "NSEW")
                && ft_arroud_player(cub, i, j, data))
                flag++;
            j++;
        }
        i++;
    }
    if (flag == 0)
        print_error("", "you don't have palyer in map", 1);
    if (flag > 1)
        print_error("", "you should have only one player", 1);
}

void	ft_check_cub(t_map map, int row, int col)
{
	if ((row == 0 && ft_check_wall(map.cub, row, col))
		|| (row == map.row - 1 && ft_check_wall(map.cub, row, col)))
		print_error("", "Erorr in wall", 1);
	else if (col == 0 && ft_check_wall(map.cub, row, col))
		print_error("", "Erorr in wall", 1);
	else if (col == (int)ft_strlen(map.cub[row]) - 1
		&& ft_check_wall(map.cub, row, col))
		print_error("", "Erorr in wall", 1);
	else if ((row > 0 && row < map.row - 1)
		&& (col > 0 && col < (int)ft_strlen(map.cub[row]) - 1))
	{
		if (map.cub[row][col] == '0'
			&& (map.cub[row + 1][col] == ' ' || map.cub[row - 1][col] == ' '
			|| map.cub[row][col + 1] == ' ' || map.cub[row][col - 1] == ' '))
			print_error("", "Erorr in wall", 1);
	}
}

void    ft_last_pars_cub(t_map map)
{
    int row;
    int col;

    row = 0;
    while (map.cub[row])
    {
        col = 0;
        if (ft_pars_wall(map.cub, row))
            print_error("", "Erorr in map", 1);
        while(map.cub[row][col])
        {
            ft_check_cub(map, row, col);
            col++;
        }
        row++;
    }
}