/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:12:44 by dagomez           #+#    #+#             */
/*   Updated: 2023/06/30 12:34:36 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_void(void)
{
	system("leaks -q fdf");
}

int	env_deploy(t_line *vec, t_coord *meta, t_env *data, char *s)
{
	meta->map_high_x = 0;
	meta->map_high_y = 0;
	meta->map_high_z = 0;
	meta->map_low_x = 0;
	meta->map_low_y = 0;
	meta->map_len_x = 0;
	meta->map_len_y = 0;
	read_map(s, meta);
	create_map(meta);
	draw_map(vec, meta, data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	free(meta->x);
	free(meta->y);
	free_t_coord(meta->z, meta);
	return (0);
}

	//atexit(ft_void);

int	main(int argc, char **argv)
{
	t_env	data;
	t_line	vec;
	t_coord	meta;

	if (argc != 2)
		out_error("Error: wrong number of arguments\n");
	meta.fd = open(argv[1], O_RDONLY);
	if (meta.fd == -1)
		out_error("Error: file does not exist\n");
	data.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	env_deploy(&vec, &meta, &data, argv[1]);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	close(meta.fd);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
