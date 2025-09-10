/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:23:12 by lucabohn          #+#    #+#             */
/*   Updated: 2025/09/10 15:49:21 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	hsv_to_rgb(double h, double s, double v, t_color *color)
{
	double	c = v * s;
	double	x = c * (1 - fabs(fmod(h/60.0, 2) - 1));
	double	m = v - c;

	double r1, g1, b1;
	if (h < 60)      { r1 = c; g1 = x; b1 = 0; }
	else if (h < 120){ r1 = x; g1 = c; b1 = 0; }
	else if (h < 180){ r1 = 0; g1 = c; b1 = x; }
	else if (h < 240){ r1 = 0; g1 = x; b1 = c; }
	else if (h < 300){ r1 = x; g1 = 0; b1 = c; }
	else             { r1 = c; g1 = 0; b1 = x; }

	color->r = (unsigned char)((r1 + m) * 255);
	color->g = (unsigned char)((g1 + m) * 255);
	color->b = (unsigned char)((b1 + m) * 255);
}


void	color_greading(int it, int max_it, t_vec2 *vec, t_color *color)
{
	if (it == max_it)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		double new_it = (double)it + 1.0 - log(log(vec->x + vec->y) / 2.0) / log(2.0);
		hsv_to_rgb(powf((new_it / (double)max_it) * 360.0, 1.5), 1, 1, color);
	}
}

void	calc_mandelbrot(double real, double imaginary, t_color *color, t_data *data)
{
	int		it;
	int		max_it;
	t_vec2	vec;
	t_vec2	vec2;
	t_vec2	prev_vec;

	it = 0.0;
	vec.x = 0.0;
	vec.y = 0.0;
	vec2.x = 0.0;
	vec2.y = 0.0;
	prev_vec.x = 0.0;
	prev_vec.y = 0.0;
	max_it = 1000 + (50 * log10(data->zoom));
	while (vec2.x + vec2.y <= 4 && it < max_it)
	{
		vec.y = 2 * vec.x * vec.y + imaginary;
		vec.x = vec2.x - vec2.y + real;
		vec2.x = vec.x * vec.x;
		vec2.y = vec.y * vec.y;
		++it;
		if (it % 20 == 0)
		{
			if (fabs(vec.x - prev_vec.x) < 1e-12
				&& fabs(vec.y - prev_vec.y) < 1e-12)
			{
				it = max_it;
				break ;
			}
			prev_vec.x = vec.x;
			prev_vec.y = vec.y;
		}
	}
	color_greading(it, max_it, &vec2, color);
}

void	calc_julia(double real, double imaginary, t_color *color, t_data *data)
{
	int		it;
	int		max_it;
	t_vec2	vec;
	t_vec2	vec2;
	t_vec2	prev_vec;

	it = 0.0;
	vec.x = real;
	vec.y = imaginary;
	vec2.x = 0.0;
	vec2.y = 0.0;
	prev_vec.x = 0.0;
	prev_vec.y = 0.0;
	max_it = 100 + (50 * log10(data->zoom));
	while (vec2.x + vec2.y <= 4 && it < max_it)
	{
		vec2.x = vec.x * vec.x;
		vec2.y = vec.y * vec.y;
		vec.y = 2 * vec.x * vec.y + data->zi;
		vec.x = vec2.x - vec2.y + data->zr;
		++it;
		if (it % 20 == 0)
		{
			if (fabs(vec.x - prev_vec.x) < 1e-12
				&& fabs(vec.y - prev_vec.y) < 1e-12)
			{
				it = max_it;
				break ;
			}
			prev_vec.x = vec.x;
			prev_vec.y = vec.y;
		}
	}
	color_greading(it, max_it, &vec2, color);
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
