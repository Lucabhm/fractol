/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_greading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:29:25 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 15:44:46 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	hsv_to_rgb(double h, t_color *color)
{
	double	x;
	t_color	tmp;

	x = 1 * (1 - fabs(fmod(h / 60.0, 2) - 1));
	if (h < 120)
		color_circle_1(&tmp, h, x);
	else if (h < 240)
		color_circle_2(&tmp, h, x);
	else
		color_circle_3(&tmp, h, x);
	color->r = (unsigned char)(tmp.r * 255);
	color->g = (unsigned char)(tmp.g * 255);
	color->b = (unsigned char)(tmp.b * 255);
}

void	color_circle_1(t_color *tmp, double h, double x)
{
	if (h < 60)
	{
		tmp->r = 1;
		tmp->g = x;
		tmp->b = 0;
	}
	else if (h < 120)
	{
		tmp->r = x;
		tmp->g = 1;
		tmp->b = 0;
	}
}

void	color_circle_2(t_color *tmp, double h, double x)
{
	if (h < 180)
	{
		tmp->r = 0;
		tmp->g = 1;
		tmp->b = x;
	}
	else if (h < 240)
	{
		tmp->r = 0;
		tmp->g = x;
		tmp->b = 1;
	}
}

void	color_circle_3(t_color *tmp, double h, double x)
{
	if (h < 300)
	{
		tmp->r = x;
		tmp->g = 0;
		tmp->b = 1;
	}
	else if (h > 300 && h < 360)
	{
		tmp->r = 1;
		tmp->g = 0;
		tmp->b = x;
	}
}

void	color_greading(int it, int max_it, t_vec2 *vec, t_color *color)
{
	double	new_it;

	if (it == max_it)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		new_it = (double)it + 1.0 - log(log(vec->x + vec->y) / 2.0) / log(2.0);
		hsv_to_rgb(powf((new_it / (double)max_it) * 360.0, 1.5), color);
	}
}
