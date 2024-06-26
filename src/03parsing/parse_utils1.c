/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/18 11:48:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_int(char **str)
{
	int	num;

	num = 0;
	while (**str == ' ')
	{
		(*str)++;
	}
	if (!ft_isdigit(**str))
		return (-1);
	while (**str >= '0' && **str <= '9' && **str != ',' && **str != '\0')
	{
		if (num > 255)
			return (-1);
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	if (num < 0 || num > 255)
	{
		return (-1);
	}
	if (**str == ' ')
		return (-1);
	if (**str != '\0' && **str != ',')
		return (-1);
	return (num);
}

int	check_texture_file(char *file_name, t_data *data)
{
	int		fd;

	(void) data;
	if (!check_xpm_extension(file_name))
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		if (errno && (errno == EISDIR || errno == ENOENT || errno == EACCES))
			return (0);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (1);
}

unsigned long	rgb_to_hex(t_rgb color)
{
	return (((unsigned long)color.red << 16) | \
		((unsigned long)color.green << 8) | \
			(unsigned long)color.blue);
}

void	cleanup_and_exit(t_cleanup_params *params)
{
	if (params->line)
	{
		free(params->line);
		params->line = NULL;
	}
	if (*(params->bb_str))
	{
		free(*(params->bb_str));
		params->bb_str = NULL;
	}
	if (params->fd)
		close(params->fd);
	if ((params->error_code) && params->error_code > 0)
		display_error(get_error_message(params->error_code), params->data);
}

void	handle_error(t_data *data, bool *flags, t_cleanup_params *params)
{
	(void) data;
	params->error_code = check_tex_col(params->data, flags[1], flags[2]);
	if (params->error_code != 0)
	{
		cleanup_and_exit(params);
	}
}
