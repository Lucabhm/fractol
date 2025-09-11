/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:54:15 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 13:53:03 by lbohm            ###   ########.fr       */
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
	data->img_ptr = mlx_new_image(data->win_ptr,
			data->win_width, data->win_height);
	if (!data->img_ptr)
		error(3, data);
	mlx_image_to_window(data->win_ptr, data->img_ptr, 0, 0);
	data->moved = true;
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	double	change_x;
	double	change_y;

	data = param;
	change_x = 0.0;
	change_y = 0.0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		error(0, data);
	else if (keydata.key == MLX_KEY_UP && keydata.action == 1)
		change_y = -0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == 1)
		change_y = 0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 1)
		change_x = -0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == 1)
		change_x = 0.1 / data->zoom;
	data->x_max += change_x;
	data->x_min += change_x;
	data->y_max += change_y;
	data->y_min += change_y;
	data->moved = true;
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	t_vec2	mouse_norm;
	int32_t	x_mouse;
	int32_t	y_mouse;

	data = param;
	mlx_get_mouse_pos(data->win_ptr, &x_mouse, &y_mouse);
	mouse_norm.x = (double)x_mouse / (double)data->win_width;
	mouse_norm.y = (double)y_mouse / (double)data->win_height;
	scroll_util(xdelta, ydelta, mouse_norm, data);
	data->moved = true;
}

void	scroll_util(double xdelta, double ydelta,
			t_vec2 mouse_norm, t_data *data)
{
	t_vec2	range;
	t_vec2	mouse_new;
	double	zoom_factor;
	t_vec2	range_new;

	range.x = data->x_max - data->x_min;
	range.y = data->y_max - data->y_min;
	mouse_new.x = data->x_min + mouse_norm.x * range.x;
	mouse_new.y = data->y_min + mouse_norm.y * range.y;
	if (ydelta + xdelta > 0)
		zoom_factor = 1.1;
	else
		zoom_factor = 0.9;
	data->zoom *= zoom_factor;
	range_new.x = range.x / zoom_factor;
	range_new.y = range.y / zoom_factor;
	data->x_min = mouse_new.x - mouse_norm.x * range_new.x;
	data->x_max = data->x_min + range_new.x;
	data->y_min = mouse_new.y - mouse_norm.y * range_new.y;
	data->y_max = data->y_min + range_new.y;
}
