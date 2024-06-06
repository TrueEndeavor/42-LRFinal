/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:51:42 by rogalio           #+#    #+#             */
/*   Updated: 2024/06/05 12:12:33 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calculate_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->game.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->game.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

int	calculate_tex_x(t_data *data, t_ray *ray, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)(data->textures.east_width));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = data->textures.east_width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = data->textures.east_width - tex_x - 1;
	return (tex_x);
}

int	get_wall_color(t_data *data, t_ray *ray, int tx, int ty)
{
	int	col;

	if (ray->side == 0 && ray->ray_dir_x < 0)
		col = data->textures.north_data[ty * data->textures.north_width + tx];
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		col = data->textures.south_data[ty * data->textures.south_width + tx];
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		col = data->textures.west_data[ty * data->textures.west_width + tx];
	else
		col = data->textures.east_data[ty * data->textures.east_width + tx];
	if (ray->side == 1)
		col = (col >> 1) & 8355711;
	return (col);
}

void	draw_wall_column(t_data *data, t_ray *ray, int *img_data, int *params)
{
	int	tex_y;
	int	color;
	int	d;

	while (ray->draw_start < ray->draw_end)
	{
		d = ray->draw_start * 256 - data->win_height * 128 + \
			ray->line_height * 128;
		tex_y = ((d * data->textures.east_height) / ray->line_height) / 256;
		color = get_wall_color(data, ray, params[1], tex_y);
		img_data[ray->draw_start * data->win_width + params[0]] = color;
		ray->draw_start++;
	}
}

void	draw_wall(t_data *data, int x, t_ray *ray, int *img_data)
{
	double	wall_x;
	int		tex_x;
	int		params[2];

	wall_x = calculate_wall_x(data, ray);
	tex_x = calculate_tex_x(data, ray, wall_x);
	params[0] = x;
	params[1] = tex_x;
	draw_wall_column(data, ray, img_data, params);
}
