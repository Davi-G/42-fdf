/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:48:53 by davi-g            #+#    #+#             */
/*   Updated: 2023/05/25 23:48:53 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	hook(void *param)
{
	t_env	*data;
	mlx_t	*mlx;

	data = param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	free_array(char **a)
{
	int	i;

	i = -1;
	while (a[++i])
		free(a[i]);
	free(a);
	return ;
}

void	free_t_coord(t_point **d, t_coord *a)
{
	int	i;

	i = 0;
	while (i < a->map_len_y)
	{
		free(d[i]);
		i++;
	}
	free(d);
}

void	out_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	len_map(char **a)
{
	int	i;

	i = 0;
	while (a[i] != NULL)
		i++;
	return (i);
}
