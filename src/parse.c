/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:46:41 by dagomez           #+#    #+#             */
/*   Updated: 2023/07/27 23:59:55 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	read_map(char *vec, t_coord *meta)
{
	int		fd;
	char	*line;
	char	**nums;

	fd = open(vec, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		meta->map_len_y++;
		nums = ft_split(line, ' ');
		if (meta->map_len_x == 0)
			meta->map_len_x = len_map(nums);
		if (meta->map_len_x != len_map(nums))
		{
			free_array(nums);
			free(line);
			out_error("Error: map is not valid\n");
		}
		free_array(nums);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	create_map(t_coord *meta)
{
	meta->z = (t_point **)ft_calloc(sizeof(t_point *), (meta->map_len_y));
	if (!meta->z)
		out_error("Error: malloc failed\n");
	meta->map_count_y = 0;
	meta->map_line = get_next_line(meta->fd);
	while (meta->map_line != NULL
		|| meta->map_count_y < meta->map_len_y)
	{
		meta->map_split = ft_split(meta->map_line, ' ');
		meta->z[meta->map_count_y] = (t_point *)ft_calloc(sizeof(t_point),
				(meta->map_len_x));
		if (!(meta->z))
			out_error("Error: malloc failed\n");
		meta->map_count_x = -1;
		while (++meta->map_count_x < meta->map_len_x)
			add_coord(meta);
		meta->map_count_y++;
		free_array(meta->map_split);
		free(meta->map_line);
		meta->map_line = get_next_line(meta->fd);
	}
	free(meta->map_line);
}

void	add_coord(t_coord *meta)
{
	long long	aux;

	aux = ft_atol(meta->map_split[meta->map_count_x]);
	if (aux > 2000 || aux < -2000)
		out_error("Error: map is not valid\n");
 	if (meta->map_high_z < aux)
		meta->map_high_z = aux;
/*	if (meta->map_low > aux)
		meta->map_low = aux; */
	meta->z[meta->map_count_y][meta->map_count_x].altitude = aux;
}


	/* int i = 0;
	int j;
	while(meta->Z[i])
	{
		j = 0;
		while (j < meta->map_len_x)
		{
			printf("%d ", meta->Z[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("X = %d\n", meta->map_len_x);
	printf("Y = %d\n", meta->map_len_y); */
