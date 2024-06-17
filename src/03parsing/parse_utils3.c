/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/17 11:08:47 by lannur-s         ###   ########.fr       */
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

void	process_basic_lines(t_data *data, char *line, bool *flags, \
	t_cleanup_params *params)
{
	if (!flags[0])
	{
		check_basic(data, line);
		if (is_texture_line(line) || is_color_line(line))
		{
			process_texture_or_color(line, data, flags);
		}
		else if (is_map_line(line))
		{
			if (flags[1] && flags[2])
			{
				handle_error(data, flags, params);
			}
			flags[0] = true;
		}
	}
}

bool	should_process_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	return (is_map_line(line) || len != 1);
}

bool	process_valid_map_line(char *line, t_data *data)
{
	int	len;

	len = validate_and_replace_spaces(line);
	if (len > 0 || line[0] == '\n')
	{
		if (load_map(data, line))
		{
			data->map_height++;
			return (true);
		}
	}
	return (false);
}

void	handle_invalid_map_line(char *line, t_data *data, int fd, char **bb_str)
{
	t_cleanup_params	params;

	free(line);
	line = NULL;
	params.data = data;
	params.line = line;
	params.fd = fd;
	params.error_code = 32;
	params.bb_str = bb_str;
	cleanup_and_exit(&params);
}
