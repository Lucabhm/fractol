/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:34:44 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 13:35:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	error(int msg, t_data *data)
{
	if (msg != 0)
		ft_printf("Error: ");
	if (msg == 1)
	{
		ft_printf("wrong nbr of arguments\n\n");
		ft_printf("input looks like ./fractol \"type of fractal\"\n\n");
		ft_printf("fractal types are: \"Mandelbrot\",");
		ft_printf(" \"Julia zr: float zi: float\" or \"Fern\"\n");
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
