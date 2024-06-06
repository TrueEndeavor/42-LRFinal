/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:18 by rogalio           #+#    #+#             */
/*   Updated: 2024/06/05 11:26:25 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_ray_parameters(t_data *data, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)data->win_width - 1;
	ray->ray_dir_x = data->game.dir_x + data->game.plane_x * ray->camera_x;
	ray->ray_dir_y = data->game.dir_y + data->game.plane_y * ray->camera_x;
	ray->map_x = (int)data->game.pos_x;
	ray->map_y = (int)data->game.pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	initialize_ray_steps(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->game.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->game.pos_x) * \
			ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->game.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->game.pos_y) * \
			ray->delta_dist_y;
	}
}
