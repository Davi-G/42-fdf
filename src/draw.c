/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:37:50 by dagomez           #+#    #+#             */
/*   Updated: 2023/06/30 14:37:14 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw(t_line *vec, t_env *data)
{
	vec->err = vec->dx - vec->dy;
	if (vec->x1 < vec->x2)
		vec->xi = 1;
	else
		vec->xi = -1;
	if (vec->y1 < vec->y2)
		vec->yi = 1;
	else
		vec->yi = -1;
	while (vec->x1 != vec->x2 && vec->y1 != vec->y2)
	{
		if (vec->x1 > 0 && vec->y1 > 0)
			mlx_put_pixel(data->image, vec->x1, vec->y1, vec->color);
		vec->err2 = 2 * vec->err;
		if (vec->err2 > -vec->dy)
		{
			vec->err -= vec->dy;
			vec->x1 += vec->xi;
		}
		if (vec->err2 < vec->dx)
		{
			vec->err += vec->dx;
			vec->y1 += vec->yi;
		}
	}
}

void	get_draw(t_coord *meta)
{
	int	i;
	int	j;
	int	y_bajo;

	y_bajo = 0;
	meta->y = ft_calloc(sizeof(int), meta->map_len_y);
	meta->x = ft_calloc(sizeof(int), meta->map_len_x);
	meta->map_high_x = fabs((meta->map_len_x) * cos(0.523599f));
	meta->map_low_x = fabs((meta->map_len_x) * cos(0.523599f));
	y_bajo = fabs((-meta->z[meta->map_len_y - 1][meta->map_len_x - 1].altitude
				+ meta->map_len_y + meta->map_len_x) * sin(0.523599f));
	meta->scale = ((1080) / (meta->map_high_x)) / 2;
	meta->map_high_x *= meta->scale;
	meta->map_low_x *= meta->scale;
	meta->hal_x = (WIDTH - (meta->map_high_x - meta->map_low_x)) / 2;
	meta->hal_y = (HEIGHT - y_bajo) / 5;
	i = -1;
	while (++i < meta->map_len_y)
	{
		j = -1;
		meta->y[i] = i * meta->scale;
		while (++j < meta->map_len_x)
			meta->x[j] = j * meta->scale;
	}
}

void	condition_1(t_line *vec, t_coord *meta, int i, int j)
{
	vec->y1 = ((-meta->z[i][j].altitude + meta->x[j] + meta->y[i])
			* sin(0.523599f));
	vec->y2 = ((-meta->z[i][j + 1].altitude + meta->x[j + 1] + meta->y[i])
			* sin(0.523599f));
	vec->x1 = ((meta->x[j] - meta->y[i]) * cos(0.523599f));
	vec->x2 = ((meta->x[j + 1] - meta->y[i]) * cos(0.523599f));
	vec->x2 += meta->hal_x;
	vec->x1 += meta->hal_x;
	vec->y1 += meta->hal_y;
	vec->y2 += meta->hal_y;
	vec->dx = abs(vec->x2 - vec->x1);
	vec->dy = abs(vec->y2 - vec->y1);
	if (meta->z[i][j].altitude == 0)
		vec->color = 0xDDDDDD;
	else
		vec->color = 0xFF00FF;
}

void	condition_2(t_line *vec, t_coord *meta, int i, int j)
{
	vec->y1 = ((-meta->z[i][j].altitude + meta->x[j] + meta->y[i])
			* sin(0.523599f));
	vec->y2 = ((-meta->z[i + 1][j].altitude + meta->x[j] + meta->y[i + 1])
			* sin(0.523599f));
	vec->x1 = ((meta->x[j] - meta->y[i]) * cos(0.523599f));
	vec->x2 = ((meta->x[j] - meta->y[i + 1]) * cos(0.523599f));
	vec->x1 += meta->hal_x;
	vec->x2 += meta->hal_x;
	vec->y1 += meta->hal_y;
	vec->y2 += meta->hal_y;
	vec->dx = abs(vec->x2 - vec->x1);
	vec->dy = abs(vec->y2 - vec->y1);
	if (meta->z[i][j].altitude == 0)
		vec->color = 0xDDDDDD;
	else
		vec->color = 0xFF00FF;
}

void	draw_map(t_line *vec, t_coord *meta, t_env *data)
{
	int	i;
	int	j;

	i = -1;
	get_draw(meta);
	while (++i < meta->map_len_y)
	{
		j = -1;
		while (++j + 1 < meta->map_len_x)
		{
			condition_1(vec, meta, i, j);
			draw(vec, data);
		}
		j = -1;
		while (++j < meta->map_len_x)
		{
			if (i + 1 < meta->map_len_y)
			{
				condition_2(vec, meta, i, j);
				draw(vec, data);
			}
		}
	}
}
