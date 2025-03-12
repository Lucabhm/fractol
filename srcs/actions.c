/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:54:15 by lbohm             #+#    #+#             */
/*   Updated: 2025/03/12 16:50:01 by lbohm            ###   ########.fr       */
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
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
		error(0, data);
	else if (keydata.key == MLX_KEY_UP && (keydata.action == 1 || keydata.action == 2))
		data->y_offset += 0.1;
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == 1 || keydata.action == 2))
		data->y_offset -= 0.1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == 1 || keydata.action == 2))
		data->x_offset += 0.1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == 1 || keydata.action == 2))
		data->x_offset -= 0.1;
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	double	zoom_factor;
	int32_t	x_pos;
	int32_t	y_pos;
	double	x_tmp;
	double	y_tmp;

	data = param;
	mlx_get_mouse_pos(data->win_ptr, &x_pos, &y_pos);
	printf("xpos = %i ypos = %i\n", x_pos, y_pos);
	x_tmp = -1.0 + (2.0 * (double)x_pos / data->win_width);
	y_tmp = -1.0 + (2.0 * (double)y_pos / data->win_height);
	printf("after\nxpos = %f ypos = %f\n", x_tmp, y_tmp);
	if (x_tmp > 0)
		data->x_offset += 0.1;
	else
		data->x_offset -= 0.1;
	if (y_tmp > 0)
		data->y_offset += 0.1;
	else
		data->y_offset -= 0.1;
	zoom_factor = 1.0 + (ydelta + xdelta) * 0.1;
	data->zoom *= zoom_factor;
	printf("zoom = %f\n", data->zoom);
}
