/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:07 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/08 19:58:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_and_replace_spaces(char *line)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == ' ')
			line[i] = '1';
		i++;
	}
	return (len);
}

int	process_map_line(char *line, t_data *data)
{
	int	len;

	len = ft_strlen(line);
	if (!is_map_line(line) && len == 1)
		return (0);
	if (is_map_line(line))
	{
		len = validate_and_replace_spaces(line);
		if (len > 0 || line[0] == '\n')
		{
			if (load_map(data, line))
				data->map_height++;
			else
			{
				on_destroy(data);
				return (0);
			}
		}
	}
	else
	{
		display_error("Invalid char in map");
		return (0);
	}
	return (1);
}

void	process_line(t_data *data, char *line, bool *flags)
{
	if (!line)
	{
		on_destroy(data);
		return ;
	}
	trim_newline(line, flags[0]);
	if (!flags[0])
	{
		check_basic(data, line);
		if (is_texture_line(line) || is_color_line(line))
			process_texture_or_color(line, data, flags);
		else if (is_map_line(line))
		{
			if (flags[1] && flags[2])
				handle_error(data, flags[1], flags[2]);
			flags[0] = true;
		}
	}
	if (flags[0] && !process_map_line(line, data))
		display_error("Map is not the last of the file");
	free(line);
}

void	parse_scene_file(t_data *data, char *scene_file)
{
	int		fd;
	char	*line;
	bool	flags[3];
	int		error_code;

	flags[0] = false;
	flags[1] = false;
	flags[2] = false;
	error_code = 0;
	fd = check_readable(data, scene_file);
	line = get_next_line(fd);
	if (!line)
	{
		display_error("The file is empty");
		on_destroy(data);
		return ;
	}
	while (line)
	{
		process_line(data, line, flags);
		line = get_next_line(fd);
	}
	error_code = check_tex_col(data, flags[1], flags[2]);
	cleanup_and_exit(data, line, fd, error_code);
}
