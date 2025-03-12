/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:08 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/12 16:49:55 by lbohm            ###   ########.fr       */
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
		data->x_offset = -0.5;
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
	data->y_offset = 0.0;
}

void	loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_resize_hook(data->win_ptr, resize, data);
	mlx_key_hook(data->win_ptr, key, data);
	mlx_scroll_hook(data->win_ptr, scroll, data);
	create_fractal(data);
}

void	create_fractal(t_data *data)
{
	int		x;
	int		y;
	float	real;
	float	imaginary;
	t_color	color = {0, 0, 0};

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			real = (-2.0 + data->x_offset) + ((4.0 / data->zoom) * (float)x / data->win_width);
			imaginary = (-2.0 + data->y_offset) + ((4.0 / data->zoom) * (float)y / data->win_height);
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
	while (it < 30.0)
	{
		z_real_tmp = z_real * z_real - z_imaginary * z_imaginary + real;
		z_imaginary_tmp = 2 * z_real * z_imaginary + imaginary;

		z_real = z_real_tmp;
		z_imaginary = z_imaginary_tmp;
		if (sqrtf(z_real * z_real + z_imaginary * z_imaginary) > 2.0)
			break ;
		++it;
	}
	if (it == 30.0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		float	tmp = sqrtf(z_real * z_real + z_imaginary * z_imaginary);
		float	diff = it + 1 - (log(log(tmp)) / log(2));
		color->r = 252 + diff * (20 - 252);
		color->g = 190 + diff * (10 - 190);
		color->b = 17 + diff * (222 - 17);
		color->r = color->r > 255 ?  255 : color->r;
		color->g = color->g > 255 ?  255 : color->g;
		color->b = color->b > 255 ?  255 : color->b;
	}
}

uint32_t	create_color(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
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
	{
		if (data->img_ptr)
			mlx_delete_image(data->win_ptr, data->img_ptr);
		if (data->win_ptr)
			mlx_terminate(data->win_ptr);

	}
	exit(msg);
}
