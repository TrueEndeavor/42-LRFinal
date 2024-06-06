/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/05 18:09:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_invalid_line(char *line)
{
	return (!(is_texture_line(line) || \
		is_color_line(line) || is_map_line(line)));
}

void	parse_line(char *line, t_data *data, bool *tex_flag, bool *col_flag)
{
	if (line == NULL)
		return ;
	trim_whitespace(&line);
	if (is_texture_line(line))
	{
		parse_texture_line(line, &data->textures);
		*tex_flag = true;
	}
	else if (is_color_line(line))
	{
		parse_color_line(line, &data->colors);
		*col_flag = true;
	}
}

void	process_texture_or_color(char *line, t_data *data, bool *flags)
{
	parse_line(line, data, &flags[1], &flags[2]);
}

void	check_basic(t_data *data, char *line)
{
	if (ft_strlen(line) <= 0 && !is_invalid_line(line))
	{
		display_error("Unknown texture/color line format");
		on_destroy(data);
		free(line);
		exit(EXIT_FAILURE);
	}
}
