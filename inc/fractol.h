/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:42 by lucabohn          #+#    #+#             */
/*   Updated: 2025/09/15 11:40:07 by lbohm            ###   ########.fr       */
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
	double		zr;
	double		zi;
	bool		moved;
}				t_data;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2;

// main.c

void		init_data(int size, char **argv, t_data *data);
void		loop(void *param);
void		create_fractal(t_data *data, t_color *color);
uint32_t	create_color(t_color *color);

// actions.c

void		resize(int width, int height, void *param);
void		key(mlx_key_data_t keydata, void *param);
void		scroll(double xdelta, double ydelta, void *param);
void		scroll_util(double xdelta, double ydelta,
				t_vec2 mouse_norm, t_data *data);

// calculation.c

void		calc_mandelbrot(double real, double imaginary,
				t_color *color, t_data *data);
void		calc_julia(double real, double imaginary,
				t_color *color, t_data *data);
bool		check_inf(int *it, int max_it, t_vec2 vec);
void		calc_fern(t_data *data, t_color *color);

// utils.c

float		ft_atof(char *input);
void		extract_float(float *result, char *input);
bool		check_input(char *input);
void		check_type(int size, char **argv, t_data *data);
void		get_coord_size(t_data *data);

// error.c

void		error(int msg, t_data *data);

// fern_calculation.c

void		transform(double *x, double *y, t_color *color);
void		fern_stem(t_vec2 *next, double y, t_color *color);
void		fern_small_leaf(t_vec2 *next, double x, double y, t_color *color);
void		fern_big_left_leaf(t_vec2 *next, double x,
				double y, t_color *color);
void		fern_big_right_leaf(t_vec2 *next, double x,
				double y, t_color *color);

// color_greading.c

void		color_greading(int it, int max_it, t_vec2 *vec, t_color *color);
void		hsv_to_rgb(double h, t_color *color);
void		color_circle_1(t_color *tmp, double h, double x);
void		color_circle_2(t_color *tmp, double h, double x);
void		color_circle_3(t_color *tmp, double h, double x);

#endif