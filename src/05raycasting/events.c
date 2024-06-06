/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:13:51 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/05 18:32:08 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	on_keypress(int key, t_data *data)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.6;
	rot_speed = 0.3;
	if (key == 65307)
	{
		on_destroy(data);
		exit(0);
	}
	if (key == 119)
		move_up(data, move_speed);
	if (key == 115)
		move_down(data, move_speed);
	if (key == 97)
		move_left(data, move_speed);
	if (key == 100)
		move_right(data, move_speed);
	if (key == 65361)
		rotate_left(data, rot_speed);
	if (key == 65363)
		rotate_right(data, rot_speed);
	return (0);
}

void	rotate(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->game.dir_x;
	data->game.dir_x = data->game.dir_x * cos(rot_speed) - \
		data->game.dir_y * sin(rot_speed);
	data->game.dir_y = old_dir_x * sin(rot_speed) + \
		data->game.dir_y * cos(rot_speed);
	old_plane_x = data->game.plane_x;
	data->game.plane_x = data->game.plane_x * cos(rot_speed) - \
		data->game.plane_y * sin(rot_speed);
	data->game.plane_y = old_plane_x * sin(rot_speed) + \
		data->game.plane_y * cos(rot_speed);
}

int	on_mouse(int x, int y, t_data *data)
{
	static int	last_x;
	int			diff_x;
	double		rot_speed;

	(void)data;
	(void)y;
	rot_speed = 0.02;
	if (last_x == 0)
		last_x = x;
	diff_x = x - last_x;
	if (diff_x > 0)
		rotate(data, -rot_speed);
	else if (diff_x < 0)
		rotate(data, rot_speed);
	last_x = x;
	return (0);
}
