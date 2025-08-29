/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:08 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/17 22:10:46 by lucabohn         ###   ########.fr       */
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
		data->type = 0;
	else if (!ft_strncmp(type, "Julia", ft_strlen(type)))
		data->type = 1;
	else if (!ft_strncmp(type, "Fern", ft_strlen(type)))
		data->type = 2;
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
	if (data->type != 2)
	{
		data->x_max = 2.0;
		data->x_min = -2.0;
		data->y_max = 2.0;
		data->y_min = -2.0;
	}
	else
	{
		data->x_max = 5;
		data->x_min = 2.5;
		data->y_max = 10.0;
		data->y_min = 10.0;
	}
	data->moved = true;
}

void	loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_resize_hook(data->win_ptr, resize, data);
	mlx_key_hook(data->win_ptr, key, data);
	mlx_scroll_hook(data->win_ptr, scroll, data);
	if (data->moved)
		create_fractal(data);
	data->moved = false;
}

void	create_fractal(t_data *data)
{
	int		x;
	int		y;
	double	real;
	double	imaginary;
	t_color	color = {0, 0, 0};

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (data->type != 2)
			{
				real = data->x_min + ((data->x_max - data->x_min) * (double)x / (double)data->win_width);
				imaginary = data->y_min + ((data->y_max - data->y_min) * (double)y / (double)data->win_height);
			}
			if (data->type == 0)
				calc_mandelbrot(real, imaginary, &color);
			else if (data->type == 1)
				calc_julia(real, imaginary, &color);
			mlx_put_pixel(data->img_ptr, x, y, create_color(color));
			++x;
		}
		++y;
	}
	if (data->type == 2)
		calc_fern(data);
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
		ft_printf("fractal types are: \"Mandelbrot\", \"Julia\" or \"Fern\"\n");
	}
	else if (msg == 2)
	{
		ft_printf("fractal type not found\n\n");
		ft_printf("fractal types are: \"Mandelbrot\", \"Julia\" or \"Fern\"\n");
	}
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
