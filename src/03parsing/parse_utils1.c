/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/10 18:29:52 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_int(char **str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	if (*str == NULL || **str == '\0')
	{
		return (-1);
	}
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num * sign);
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
		if (errno == EISDIR)
			//display_error("Not a file. Is a dir", data);
			return (0);
		if (errno == ENOENT)
			//display_error("File not found", data);
			return (0);
		else if (errno == EACCES)
			//display_error("File cannot be opened: Permission denied", NULL);
			return (0);
		else
			//display_error(strerror(errno), data);
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

void	cleanup_and_exit(t_data *data, char *line, int fd, int error_code)
{
printf("....in cleanup_and_exit\n");
	if (line)
	{
		printf("line before free : %s\n", line);
		free(line);
	}
	printf("error_code before free : %d\n", error_code);	
	if (error_code != 0)
	{
		display_error(get_error_message(error_code), data);
		// on_destroy(data);
	}
	if (fd)
		close(fd);
}

void	handle_error(t_data *data, bool *flags, char *line, int fd)
{
	int	error_code;
printf("....in handle error\n");
	error_code = check_tex_col(data, flags[1], flags[2]);
	cleanup_and_exit(data, line, fd, error_code);
}
