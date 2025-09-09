/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:42 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/17 21:56:25 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libs/ft_libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/mlx/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data
{
	int			type;
	int			win_width;
	int			win_height;
	mlx_t		*win_ptr;
	mlx_image_t	*img_ptr;
	double		zoom;
	double		x_max;
	double		x_min;
	double		y_max;
	double		y_min;
	bool		moved;
}				t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2;

// main.c

void		check_type(char *type, t_data *data);
void		get_coord_size(t_data *data);
void		init_data(char *type, t_data *data);
void		loop(void *param);
void		create_fractal(t_data *data);
uint32_t	create_color(t_color color);
void		error(int msg, t_data *data);

// actions.c

void		resize(int width, int height, void *param);
void		key(mlx_key_data_t keydata, void *param);
void		scroll(double xdelta, double ydelta, void *param);

// calculation.c

void		calc_mandelbrot(double real, double imaginary, t_color *color, t_data *data);
void		calc_julia(double real, double imaginary, t_color *color, t_data *data);
void		calc_fern(t_data *data);
void		transform(double *x, double *y);

#endif