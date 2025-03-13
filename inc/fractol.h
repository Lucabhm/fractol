/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:42 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/13 19:53:41 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libs/ft_libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/mlx/include/MLX42/MLX42.h"
# include <stdio.h>
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
}				t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

void		init_data(char *type, t_data *data);
void		loop(void *param);
void		resize(int width, int height, void *param);
void		key(mlx_key_data_t keydata, void *param);
void		scroll(double xdelta, double ydelta, void *param);
void		create_fractal(t_data *data);
void		calc_mandelbrot(double real, double imaginary, t_color *color);
uint32_t	create_color(t_color color);
void		error(int msg, t_data *data);

#endif