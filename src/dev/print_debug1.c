/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/06/05 13:09:28 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	print_colors(t_data *data)
{
	printf("\n****PRINT COLORS****\n");
	printf("Ceiling rgb = %d, %d, %d\n", data->colors.ceiling.red, \
		data->colors.ceiling.green, data->colors.ceiling.blue);
	printf("Ceiling count = %d\n", data->colors.ceiling_count);
	printf("Floor rgb = %d, %d, %d\n", data->colors.floor.red, \
		data->colors.floor.green, data->colors.floor.blue);
	printf("Floor count = %d\n", data->colors.floor_count);
}

void	print_content(void *c)
{
	printf("%s", (char *)c);
	printf("\n");
}

void	print_map(t_data *data)
{
	printf("\n****PRINT MAP****\n");
	ft_lstiter(data->map, &print_content);
}
