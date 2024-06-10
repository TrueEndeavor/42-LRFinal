/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:51:43 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/10 13:14:56 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_dup_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->dup_map[i])
	{
		free(data->dup_map[i]);
		i++;
	}
	free(data->dup_map);
	data->dup_map = NULL;
}

void	free_world_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		if (data->world_map[i])
			free(data->world_map[i]);
		i++;
	}
	if (data->world_map)
		free(data->world_map);
}

void	free_maps(t_data *data)
{
	t_list	*current;
	t_list	*next;

	if (data->world_map)
		free_world_map(data);
	if (data->dup_map)
		free_dup_map(data);
	if (data->map)
	{
		current = data->map;
		while (current)
		{
			free(current->content);
			next = current->next;
			free(current);
			current = next;
		}
	}
}

void	free_textures(t_data *data)
{
	if (data->textures.north_texture)
		free(data->textures.north_texture);
	if (data->textures.east_texture)
		free(data->textures.east_texture);
	if (data->textures.south_texture)
		free(data->textures.south_texture);
	if (data->textures.west_texture)
		free(data->textures.west_texture);
	data->textures.north_texture = NULL;
	data->textures.east_texture = NULL;
	data->textures.south_texture = NULL;
	data->textures.west_texture = NULL;
}

void	destroy_images(t_data *data)
{
	if (data->textures.north_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures.north_img);
		data->textures.north_img = NULL;
	}
	data->textures.north_data = NULL;
	if (data->textures.east_img)
	{	
		mlx_destroy_image(data->mlx_ptr, data->textures.east_img);
		data->textures.east_img = NULL;
	}	
	data->textures.east_data = NULL;
	if (data->textures.south_img)
	{	
		mlx_destroy_image(data->mlx_ptr, data->textures.south_img);
		data->textures.south_img = NULL;
	}	
	data->textures.south_data = NULL;
	if (data->textures.west_img)
	{	
		mlx_destroy_image(data->mlx_ptr, data->textures.west_img);
		data->textures.west_img = NULL;
	}		
	data->textures.west_data = NULL;
}

int	on_destroy(t_data *data)
{
	free_maps(data);
	free_textures(data);
	if (data->mlx_ptr)
	{
		destroy_images(data);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}
