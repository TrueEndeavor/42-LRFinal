/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:18 by rogalio           #+#    #+#             */
/*   Updated: 2024/06/05 11:23:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	increment_ray_distances(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

int	is_wall_hit(t_data *data, t_ray *ray)
{
	return (data->world_map[ray->map_x][ray->map_y] > 0);
}

void	calculate_perp_wall_dist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->game.pos_x + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->game.pos_y + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	detect_walls(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	initialize_ray_steps(data, ray);
	while (hit == 0)
	{
		increment_ray_distances(ray);
		if (is_wall_hit(data, ray))
			hit = 1;
	}
	calculate_perp_wall_dist(data, ray);
}

void	calculate_wall_parameters(t_data *data, t_ray *ray)
{
	ray->line_height = (int)(data->win_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
}
