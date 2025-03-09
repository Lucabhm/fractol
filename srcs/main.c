/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:08 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/09 18:41:40 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_data(argv[1], &data);
		create_fractal(&data);
		mlx_loop(data.window_ptr);
		mlx_terminate(data.window_ptr);
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
	else
		error(2, NULL);
	data->window_ptr = mlx_init(400, 400, "fractol", false);
	if (!data->window_ptr)
		error(3, NULL);
	data->img_ptr = mlx_new_image(data->window_ptr, 400, 400);
	if (!data->img_ptr)
		error(3, data);
	mlx_image_to_window(data->window_ptr, data->img_ptr, 0, 0);
}

void	create_fractal(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 400)
	{
		x = 0;
		while (x < 400)
		{
			mlx_put_pixel(data->img_ptr, x, y, create_color(20, 200, 150, 255));
			++x;
		}
		++y;
	}
}

uint32_t	create_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	error(int msg, t_data *data)
{
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
		mlx_terminate(data->window_ptr);
	exit(msg);
}
