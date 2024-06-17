/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:11:01 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/17 10:31:22 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map_size(t_data *data)
{
	if (ft_lstsize(data->map) <= 0)
	{
		display_error("Missing map info", data);
		return (0);
	}
	if (ft_lstsize(data->map) < 3)
	{
		display_error("The map size is too small", data);
		return (0);
	}
	return (1);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'E' || \
		c == 'S' || c == 'W' || c == ' ' || c == '\n')
	{
		return (1);
	}
	return (0);
}

int	process_chars(char *line, t_data *data)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] != '\0')
	{
		c = line[i];
		if (!is_valid_char(c))
		{
			display_error("Invalid char in map_ check_chars", data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_chars(t_data *data)
{
	t_list	*current;
	int		j;

	j = 0;
	current = data->map;
	while (current)
	{
		if (!process_chars((char *)current->content, data))
		{
			return (0);
		}
		current = current->next;
		j++;
	}
	return (1);
}
