/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:51:43 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/11 10:29:58 by lannur-s         ###   ########.fr       */
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
