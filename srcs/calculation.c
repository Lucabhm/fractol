/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:23:12 by lucabohn          #+#    #+#             */
/*   Updated: 2025/09/15 11:32:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	calc_mandelbrot(double real, double imaginary,
			t_color *color, t_data *data)
{
	int		it;
	int		max_it;
	t_vec2	vec;
	t_vec2	vec2;

	it = 0.0;
	vec.x = 0.0;
	vec.y = 0.0;
	vec2.x = 0.0;
	vec2.y = 0.0;
	max_it = 500 + (50 * log10(data->zoom));
	if (max_it < 0 || max_it > 100000)
		max_it = 100000;
	while (vec2.x + vec2.y <= 4 && it < max_it)
	{
		vec.y = 2 * vec.x * vec.y + imaginary;
		vec.x = vec2.x - vec2.y + real;
		vec2.x = vec.x * vec.x;
		vec2.y = vec.y * vec.y;
		++it;
		if (check_inf(&it, max_it, vec))
			break ;
	}
	color_greading(it, max_it, &vec2, color);
}

void	calc_julia(double real, double imaginary, t_color *color, t_data *data)
{
	int		it;
	int		max_it;
	t_vec2	vec;
	t_vec2	vec2;

	it = 0.0;
	vec.x = real;
	vec.y = imaginary;
	vec2.x = 0.0;
	vec2.y = 0.0;
	max_it = 500 + (50 * log10(data->zoom));
	if (max_it < 0 || max_it > 100000)
		max_it = 100000;
	while (vec2.x + vec2.y <= 4 && it < max_it)
	{
		vec2.x = vec.x * vec.x;
		vec2.y = vec.y * vec.y;
		vec.y = 2 * vec.x * vec.y + data->zi;
		vec.x = vec2.x - vec2.y + data->zr;
		++it;
		if (check_inf(&it, max_it, vec))
			break ;
	}
	color_greading(it, max_it, &vec2, color);
}

bool	check_inf(int *it, int max_it, t_vec2 vec)
{
	static t_vec2	prev_vec;

	prev_vec.x = 0;
	prev_vec.y = 0;
	if (*it % 20 == 0)
	{
		if (fabs(vec.x - prev_vec.x) < 1e-12
			&& fabs(vec.y - prev_vec.y) < 1e-12)
		{
			*it = max_it;
			return (true);
		}
		prev_vec.x = vec.x;
		prev_vec.y = vec.y;
	}
	return (false);
}

void	calc_fern(t_data *data, t_color *color)
{
	t_vec2	coords;
	t_vec2	pos;
	int		it;
	int		max_it;

	coords.x = 0.0;
	pos.x = 0.0;
	pos.y = 0.0;
	coords.y = 0.0;
	it = -1;
	max_it = 100000 * data->zoom;
	if (max_it < 0 || max_it > 50000000)
		max_it = 50000000;
	while (++it < max_it)
	{
		transform(&coords.x, &coords.y, color);
		pos.x = (coords.x - data->x_min) / (data->x_max - data->x_min)
			* data->win_width;
		pos.y = ((-coords.y) - data->y_min) / (data->y_max - data->y_min)
			* data->win_height;
		if ((int)pos.x > 0.0 && (int)pos.x < data->win_width && (int)pos.y
			> 0.0 && (int)pos.y < data->win_height)
			mlx_put_pixel(data->img_ptr, (int)pos.x,
				(int)pos.y, create_color(color));
	}
}
