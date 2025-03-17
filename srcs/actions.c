/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:54:15 by lbohm             #+#    #+#             */
/*   Updated: 2025/03/17 22:03:29 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

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
	data->moved = true;
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		error(0, data);
	else if (keydata.key == MLX_KEY_UP && (keydata.action == 1 || keydata.action == 2))
	{
		data->y_max -= 0.1;
		data->y_min -= 0.1;
	}
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == 1 || keydata.action == 2))
	{
		data->y_max += 0.1;
		data->y_min += 0.1;
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == 1 || keydata.action == 2))
	{
		data->x_max -= 0.1;
		data->x_min -= 0.1;
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == 1 || keydata.action == 2))
	{
		data->x_max += 0.1;
		data->x_min += 0.1;
	}
	data->moved = true;
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	double	zoom_factor;
	double	x_range;
	double	y_range;
	double	x_range_new;
	double	y_range_new;
	int32_t	x_mouse;
	int32_t	y_mouse;
	double	x_mouse_norm;
	double	y_mouse_norm;
	double	x_mouse_real;
	double	y_mouse_imag;

	data = param;
	x_range = data->x_max - data->x_min;
	y_range = data->y_max - data->y_min;
	mlx_get_mouse_pos(data->win_ptr, &x_mouse, &y_mouse);
	x_mouse_norm = (double)x_mouse / (double)data->win_width;
	y_mouse_norm = (double)y_mouse / (double)data->win_height;
	x_mouse_real = data->x_min + x_mouse_norm * x_range;
	y_mouse_imag = data->y_min + y_mouse_norm * y_range;
	if (ydelta + xdelta > 0)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	x_range_new = x_range / zoom_factor;
	y_range_new = y_range / zoom_factor;
	data->x_min = x_mouse_real - x_mouse_norm * x_range_new;
	data->x_max = data->x_min + x_range_new;
	data->y_min = y_mouse_imag - y_mouse_norm * y_range_new;
	data->y_max = data->y_min + y_range_new;
	data->moved = true;
}
