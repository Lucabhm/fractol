/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:08 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:02 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_data(argv[1], &data);
		mlx_loop_hook(data.win_ptr, loop, &data);
		mlx_loop(data.win_ptr);
		mlx_terminate(data.win_ptr);
	}
	else
		error(1, NULL);
	return (0);
}

void	init_data(char *type, t_data *data)
{
	if (!ft_strncmp(type, "Mandelbrot", ft_strlen(type)))
	{
		data->type = 0;
		data->offset = 0.5;
	}
	else if (!ft_strncmp(type, "Julia", ft_strlen(type)))
		data->type = 1;
	else
		error(2, NULL);
	data->win_width = 500;
	data->win_height = 500;
	data->win_ptr = mlx_init(data->win_width, data->win_height, "fractol", true);
	if (!data->win_ptr)
		error(3, NULL);
	data->img_ptr = mlx_new_image(data->win_ptr, data->win_width, data->win_height);
	if (!data->img_ptr)
		error(3, data);
	mlx_image_to_window(data->win_ptr, data->img_ptr, 0, 0);
	data->zoom = 1.0;
}

void	loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_resize_hook(data->win_ptr, resize, data);
	mlx_key_hook(data->win_ptr, key, data);
	mlx_scroll_hook(data->win_ptr, scroll, data);
	create_fractal(data);
	printf("time = %f\n", data->win_ptr->delta_time);
}

void	resize(int width, int height, void *param)
{
	t_data	*data;

	data = param;
	data->win_width = width;
	data->win_height = height;
	mlx_delete_image(data->win_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->win_ptr, data->win_width, data->win_height);
	if (!data->img_ptr)
		error(3, data);
	mlx_image_to_window(data->win_ptr, data->img_ptr, 0, 0);
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		error(0, data);
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = param;
	printf("xdelta = %f ydelta = %f\n", xdelta, ydelta);
	data->zoom += ydelta;
}

void	create_fractal(t_data *data)
{
	int		x;
	int		y;
	float	real;
	float	imaginary;
	t_color	color = {0, 0, 0, 0};

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			real = (-2.0 + (4 * (float)x / data->win_width) - data->offset) * data->zoom;
			imaginary = (-2.0 + (4 * (float)y / data->win_height)) * data->zoom;
			calc_mandelbrot(real, imaginary, &color);
			mlx_put_pixel(data->img_ptr, x, y, create_color(color));
			++x;
		}
		++y;
	}
}

void	calc_mandelbrot(float real, float imaginary, t_color *color)
{
	float	it;
	float	z_real;
	float	z_imaginary;
	float	z_real_tmp;
	float	z_imaginary_tmp;

	it = 0.0;
	z_real = 0.0;
	z_imaginary = 0.0;
	while (it < 1000.0)
	{
		z_real_tmp = z_real * z_real - z_imaginary * z_imaginary + real;
		z_imaginary_tmp = 2 * z_real * z_imaginary + imaginary;

		z_real = z_real_tmp;
		z_imaginary = z_imaginary_tmp;
		if (sqrtf(z_real * z_real + z_imaginary * z_imaginary) > 2.0)
			break ;
		++it;
	}
	if (it == 1000.0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
		color->a = 255;
	}
	else
	{
		float	diff = it / 1000.0;
		color->r = 252 + diff * (50 - 252);
		color->g = 190 + diff * (200 - 190);
		color->b = 17 + diff * (100 - 17);
		// color->r = 252;
		// color->g = 190;
		// color->b = 17;
		// color->r = 50;
		// color->g = 200;
		// color->b = 100;
		color->a = 255;
	}
}

uint32_t	create_color(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

void	error(int msg, t_data *data)
{
	if (msg != 0)
		ft_printf("Error: ");
	if (msg == 1)
	{
		ft_printf("wrong nbr of arguments\n\n");
		ft_printf("input looks like ./fractol \"type of fractal\"\n\n");
		ft_printf("fractal types are: \"Mandelbrot\" or \"Julia\"\n");
	}
	else if (msg == 2)
		ft_printf("fractal type not found\n");
	else if (msg == 3)
		ft_printf("NULL ptr\n");
	if (data)
		mlx_terminate(data->win_ptr);
	exit(msg);
}
