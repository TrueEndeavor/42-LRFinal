/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:07 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/17 11:21:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	process_map_line(char *line, t_data *data, int fd, char **bb_str)
{
	if (!should_process_line(line))
	{
		return (0);
	}
	if (is_map_line(line))
	{
		if (!process_valid_map_line(line, data))
		{
			on_destroy(data);
			return (0);
		}
	}
	else
	{
		handle_invalid_map_line(line, data, fd, bb_str);
		return (0);
	}
	return (1);
}

void	process_line(t_data *data, char *line, bool *flags, int fd, char **bb_str)
{
	t_cleanup_params	params;

	if (!line)
	{
		on_destroy(data);
		return ;
	}
	trim_newline(line, flags[0]);
	params.data = data;
	params.line = line;
	params.fd = fd;
	params.error_code = 0;
	params.bb_str = bb_str;
	process_basic_lines(data, line, flags, &params);
	if (flags[0] && !process_map_line(line, data, fd, bb_str))
	{
		free (line);
		cleanup_and_exit(&params);
	}
}

void	process_file(t_data *data, int fd, bool *flags, char **bb_str)
{
	char	*line;
	int		start;
	t_cleanup_params	params;

	line = NULL;
	start = 0;
	while (1)
	{
		line = get_next_line(fd, bb_str);
		if (!line && !start)
		{
			display_error("The file is empty", data);
			on_destroy(data);
			break ;
		}
		start = 1;
		if (!line && start)
			break ;
		params.data = data;
		params.line = line;
		params.fd = fd;
		params.error_code = 0;
		params.bb_str = bb_str;
		process_line(data, line, flags, fd, bb_str);
		if (line)
			free(line);
	}
}

void	parse_scene_file(t_data *data, char *scene_file)
{
	int					fd;
	bool				flags[3];
	char				*bb_str;
	t_cleanup_params	params;

	initialize_flags(flags);
	fd = check_readable(data, scene_file);
	params.data = data;
	params.line = NULL;
	params.fd = fd;
	params.error_code = check_tex_col(data, flags[1], flags[2]);
	params.bb_str = &bb_str;
	process_file(data, fd, flags, &bb_str);
}
