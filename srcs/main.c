/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:08 by lucabohn          #+#    #+#             */
/*   Updated: 2025/09/11 16:38:17 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc >= 2)
	{
		init_data(argc, argv, &data);
		mlx_loop_hook(data.win_ptr, loop, &data);
		mlx_loop(data.win_ptr);
		if (data.img_ptr)
			mlx_delete_image(data.win_ptr, data.img_ptr);
		mlx_terminate(data.win_ptr);
	}
	else
		error(1, NULL);
	return (0);
}

void	init_data(int size, char **args, t_data *data)
{
	check_type(size, args, data);
	data->win_width = 500;
	data->win_height = 500;
	data->win_ptr = mlx_init(data->win_width, data->win_height,
			"fractol", true);
	if (!data->win_ptr)
		error(3, NULL);
	data->img_ptr = mlx_new_image(data->win_ptr,
			data->win_width, data->win_height);
	if (!data->img_ptr)
		error(3, data);
	mlx_image_to_window(data->win_ptr, data->img_ptr, 0, 0);
	data->zoom = 1.0;
	get_coord_size(data);
	data->moved = true;
}

void	loop(void *param)
{
	t_data	*data;
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	data = param;
	mlx_resize_hook(data->win_ptr, resize, data);
	mlx_key_hook(data->win_ptr, key, data);
	mlx_scroll_hook(data->win_ptr, scroll, data);
	if (data->moved)
		create_fractal(data, &color);
	data->moved = false;
}

void	create_fractal(t_data *data, t_color *color)
{
	int		x;
	int		y;
	double	real;
	double	imaginary;

	y = 0;
	while (y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
		{
			real = data->x_min + ((data->x_max - data->x_min)
					* (double)x / (double)data->win_width);
			imaginary = data->y_min + ((data->y_max - data->y_min)
					* (double)y / (double)data->win_height);
			if (data->type == 0)
				calc_mandelbrot(real, imaginary, color, data);
			else if (data->type == 1)
				calc_julia(real, imaginary, color, data);
			mlx_put_pixel(data->img_ptr, x, y, create_color(color));
		}
		++y;
	}
	if (data->type == 2)
		calc_fern(data, color);
}

uint32_t	create_color(t_color *color)
{
	return ((int)color->r << 24 | (int)color->g << 16
		| (int)color->b << 8 | 255);
}
