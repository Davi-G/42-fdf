/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/02/01 15:21:11 by dagomez           #+#    #+#             */
/*   Updated: 2023/02/01 15:21:11 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# define WIDTH 1920
//# define WIDTH 1800
# define HEIGHT 1080
//# define HEIGHT 1169

typedef struct s_line
{
	int			x1;
	int			x2;

	int			y1;
	int			y2;

	int			dx;
	int			dy;

	int			xi;
	int			yi;

	int			err;
	int			err2;

	uint32_t	color;
}	t_line;

typedef struct s_point
{
	int			altitude;
	uint32_t	color;
}	t_point;

typedef struct s_coord
{
	int			fd;
	char		*map_line;
	char		**map_split;

	int			map_high_x;
	int			map_high_y;
	int			map_high_z;
	int			map_low_y;
	int			map_low_x;
	int			map_len_x;
	int			map_len_y;
	int			map_count_x;
	int			map_count_y;
	int			hal_x;
	int			hal_y;
	int			scale;

	int			*x;
	int			*y;
	t_point		**z;
}	t_coord;

typedef struct s_env
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_coord		*coord;
	t_line		*line;
	int			mid_x;
	int			mid_y;
}	t_env;

void			draw(t_line *line, t_env *data);
int				env_deploy(t_line *vec, t_coord *meta, t_env *data, char *s);
void			hook(void *param);
void			sawp(int *a, int *b);
void			create_map(t_coord *meta);
void			read_map(char *vec, t_coord *meta);
void			free_array(char **a);
void			add_coord(t_coord *meta);
int				len_map(char **a);
void			free_t_coord(t_point **d, t_coord *a);
void			free_int(int *a);
void			draw_map(t_line *vec, t_coord *meta, t_env *data);
void			get_draw(t_coord *meta);
void			condition_1(t_line *vec, t_coord *meta, int i, int j);
void			condition_2(t_line *vec, t_coord *meta, int i, int j);
void			out_error(char *s);
void			isometric_x(int z, int x, int y, t_coord *meta);

#endif