/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:07:20 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/13 11:29:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_map(t_data *data, char *line)
{
	t_list	*new;
	size_t	max_width;

	if (!line || !data)
		return (0);
	new = ft_lstnew(ft_strdup(line));
	if (!new || !new->content)
	{
		if (new)
			free(new);
		return (0);
	}
	ft_lstadd_back(&data->map, new);
	max_width = ft_strlen(line);
	if ((int)max_width > data->map_width)
		data->map_width = (int)max_width;
	return (1);
}
