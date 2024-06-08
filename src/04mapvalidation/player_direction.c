/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:08:17 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/08 20:10:21 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_direction_north(t_game *game)
{
	game->dir_x = -1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = -0.66;
}

void	set_player_direction_south(t_game *game)
{
	game->dir_x = 1;
	game->dir_y = -1;
	game->plane_x = 0;
	game->plane_y = 0.66;
}

void	set_player_direction_east(t_game *game)
{
	game->dir_x = -1;
	game->dir_y = 1;
	game->plane_x = 0.66;
	game->plane_y = 0.66;
}

void	set_player_direction_west(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	game->plane_y = 0;
}
