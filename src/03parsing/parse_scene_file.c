/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:07 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/14 18:19:01 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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

int	process_map_line(char *line, t_data *data, int fd, char **bb_str)
{
	int	len;
	t_cleanup_params	params;	

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
		free(line);
		line = NULL;
		params.data = data;
		params.line = line;
		params.fd = fd;
		params.error_code = 32;
		params.bb_str = bb_str;
		//cleanup_and_exit(data, line, fd, ERR_MAP_NOT_VALID, bb_str);
		printf("err in process map line\n");
		cleanup_and_exit(&params);
		return (0);
	}
	return (1);
}

void	process_line(t_data *data, char *line, bool *flags, int fd, char **bb_str)
{

	t_cleanup_params	params;
	
	if (!line)
	{
		printf("teste !line\n");
		on_destroy(data);
		return ;
	}
	trim_newline(line, flags[0]);
		params.data = data;
		params.line = line;
		params.fd = fd;
		params.error_code = 0;
		params.bb_str = bb_str;	
	if (!flags[0])
	{
		check_basic(data, line);
		if (is_texture_line(line) || is_color_line(line))
			process_texture_or_color(line, data, flags);
		else if (is_map_line(line))
		{
			printf("is mamp line : line = %s\n", line);
			if (flags[1] && flags[2])
				handle_error(data, flags, &params);
			//handle_error(data, flags, line, fd, bb_str);
			flags[0] = true;
		}
	}
	if (flags[0] && !process_map_line(line, data, fd, bb_str))
	{
		free (line);
		//cleanup_and_exit(data, line, fd, ERR_MAP_NOT_LAST, bb_str);
		printf("I am here\n");
		cleanup_and_exit(&params);
	}
}

void	process_file(t_data *data, int fd, bool *flags, char **bb_str)
{
	char	*line;
	int		start;

	line = NULL;
	start = 0;
	while (1)
	{
		line = get_next_line(fd, bb_str);
		printf("\n--------------------------------------\nline = %s\n", line);
		if (!line && !start)
		{
			display_error("The file is empty", data);
			on_destroy(data);
			break ;
		}
		start = 1;
		if (!line && start)
			break ;
		process_line(data, line, flags, fd, bb_str);
		if (line)
			free(line);
		printf("\nEND\n");
	}
}

void	initialize_flags(bool *flags)
{
	flags[0] = false;
	flags[1] = false;
	flags[2] = false;
}

void	parse_scene_file(t_data *data, char *scene_file)
{
	int					fd;
	bool				flags[3];
	char				*bb_str;
/* 	char				*line;
	int					error_code;
	int					start; */
	t_cleanup_params	params;

	initialize_flags(flags);
	fd = check_readable(data, scene_file);
	params.data = data;
	params.line = NULL;
	params.fd = fd;
	params.error_code = check_tex_col(data, flags[1], flags[2]);
	params.bb_str = &bb_str;

	process_file(data, fd, flags, &bb_str);
	print_textures(data);
	/* error_code = 0;
	line = NULL;
	start = 0;
	bb_str = NULL;
	while (1)
	{
		line = get_next_line(fd, &bb_str);
		printf("\n--------------------------------------\nline = %s\n", line);
		if (!line && !start)
		{
			display_error("The file is empty", data);
			on_destroy(data);
			break ;
		}
		start = 1;
		if (!line && start)
			break ;
		process_line(data, line, flags, fd, &bb_str);
		if (line)
			free (line);
		printf("\nEND\n");
	}
	error_code = check_tex_col(data, flags[1], flags[2]);
	cleanup_and_exit(data, line, fd, error_code, &bb_str); */
	//cleanup_and_exit(&params);
}
