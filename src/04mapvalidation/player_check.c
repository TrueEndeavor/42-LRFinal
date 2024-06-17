/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:54:17 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/17 17:30:03 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_for_players(t_data *data, int i, int j)
{
	int	count;

	count = 0;
	if (!data->dup_map || !data->dup_map[i] || !data->dup_map[i][j])
		return (0);
	while (ft_iswhitespace(data->dup_map[i][j]))
		j++;
	while (data->dup_map[i][j])
	{
		if (data->dup_map[i][j] == 'N' || \
			data->dup_map[i][j] == 'E' || \
			data->dup_map[i][j] == 'S' || \
			data->dup_map[i][j] == 'W')
		{
			count++;
		}
		j++;
	}
	return (count);
}

int	check_players(t_data *data)
{
	int	i;
	int	status;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < data->map_height - 1)
	{
		status = check_for_players(data, i, 0);
		if (status >= 1)
		{
			player_count += status;
		}
		i++;
	}
	if (player_count <= 0 || player_count > 1)
		return (0);
	return (1);
}
