/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:23:12 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/17 22:12:32 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	calc_mandelbrot(double real, double imaginary, t_color *color)
{
	double	it;
	double	z_real;
	double	z_imaginary;
	double	z_real_tmp;
	double	z_imaginary_tmp;

	it = 0.0;
	z_real = 0.0;
	z_imaginary = 0.0;
	while (it < 100.0)
	{
		z_real_tmp = z_real * z_real - z_imaginary * z_imaginary + real;
		z_imaginary_tmp = 2 * z_real * z_imaginary + imaginary;

		z_real = z_real_tmp;
		z_imaginary = z_imaginary_tmp;
		if (sqrt(z_real * z_real + z_imaginary * z_imaginary) > 2.0)
			break ;
		++it;
	}
	if (it == 100.0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		float	tmp = sqrt(z_real * z_real + z_imaginary * z_imaginary);
		float	diff = it + 1 - (log(log(tmp)) / log(2));
		color->r = 252 + diff * (20 - 252);
		color->g = 190 + diff * (10 - 190);
		color->b = 17 + diff * (222 - 17);
		color->r = color->r > 255 ?  255 : color->r;
		color->g = color->g > 255 ?  255 : color->g;
		color->b = color->b > 255 ?  255 : color->b;
	}
}

void	calc_julia(double real, double imaginary, t_color *color)
{
	double	it;
	double	z_real;
	double	z_imaginary;
	double	z_real_tmp;
	double	z_imaginary_tmp;

	it = 0.0;
	z_real = real;
	z_imaginary = imaginary;
	while (it < 100.0)
	{
		z_real_tmp = z_real * z_real - z_imaginary * z_imaginary + (-1.0);
		z_imaginary_tmp = 2 * z_real * z_imaginary + 0.2;

		z_real = z_real_tmp;
		z_imaginary = z_imaginary_tmp;
		if (sqrt(z_real * z_real + z_imaginary * z_imaginary) > 2.0)
			break ;
		++it;
	}
	if (it == 100.0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		double	tmp = sqrt(z_real * z_real + z_imaginary * z_imaginary);
		double	diff = it + 1 - (log(log(tmp)) / log(2));
		color->r = 252 + diff * (20 - 252);
		color->g = 190 + diff * (10 - 190);
		color->b = 17 + diff * (222 - 17);
		color->r = color->r > 255 ?  255 : color->r;
		color->g = color->g > 255 ?  255 : color->g;
		color->b = color->b > 255 ?  255 : color->b;
	}
}

void	calc_fern(t_data *data)
{
	double	x;
	double	y;
	double	pos_x;
	double	pos_y;
	int		it;
	t_color	color = {180,80,20};

	x = 0.0;
	pos_x = 0.0;
	pos_y = 0.0;
	y = 0.0;
	it = 0;
	while (it < 100000)
	{
		transform(&x, &y);
		pos_x = (x + 2.5) / 5.0 * data->win_width;
		pos_y = (10 - y) / 10.0 * data->win_height;
		if (pos_x > 0.0 && (int)pos_x < data->win_width && pos_y > 0.0 && (int)pos_y < data->win_height)
			mlx_put_pixel(data->img_ptr, (int)pos_x, (int)pos_y, create_color(color));
		++it;
	}
}

void	transform(double *x, double *y)
{
	double	random_nbr;
	double	next_x;
	double	next_y;

	random_nbr = (double)rand() / RAND_MAX;
	if (random_nbr < 0.01)
	{
		next_x = 0.0;
		next_y = 0.16 * (*y);
	}
	else if (random_nbr < 0.86)
	{
		next_x = 0.85 * (*x) + 0.04 * (*y);
		next_y = -0.04 * (*x) + 0.85 * (*y) + 1.6;
	}
	else if (random_nbr < 0.93)
	{
		next_x = 0.2 * (*x) - 0.26 * (*y);
		next_y = 0.23 * (*x) + 0.22 * (*y) + 1.6;
	}
	else
	{
		next_x = -0.15 * (*x) + 0.28 * (*y);
		next_y = 0.26 * (*x) + 0.24 * (*y) + 0.44;
	}
	*x = next_x;
	*y = next_y;
}
