/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fern_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:02:08 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 16:02:02 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	transform(double *x, double *y, t_color *color)
{
	double	random_nbr;
	t_vec2	next;

	random_nbr = (double)rand() / RAND_MAX;
	if (random_nbr < 0.01)
		fern_stem(&next, *y, color);
	else if (random_nbr < 0.86)
		fern_small_leaf(&next, *x, *y, color);
	else if (random_nbr < 0.93)
		fern_big_left_leaf(&next, *x, *y, color);
	else
		fern_big_right_leaf(&next, *x, *y, color);
	*x = next.x;
	*y = next.y;
}

void	fern_stem(t_vec2 *next, double y, t_color *color)
{
	next->x = 0.0;
	next->y = 0.16 * y;
	color->r = 80;
	color->g = 180;
	color->b = 20;
}

void	fern_small_leaf(t_vec2 *next, double x, double y, t_color *color)
{
	next->x = 0.85 * x + 0.04 * y;
	next->y = -0.04 * x + 0.85 * y + 1.6;
	color->r = 80;
	color->g = 180;
	color->b = 20;
}

void	fern_big_left_leaf(t_vec2 *next, double x, double y, t_color *color)
{
	next->x = 0.2 * x - 0.26 * y;
	next->y = 0.23 * x + 0.22 * y + 1.6;
	color->r = 80;
	color->g = 180;
	color->b = 20;
}

void	fern_big_right_leaf(t_vec2 *next, double x, double y, t_color *color)
{
	next->x = -0.15 * x + 0.28 * y;
	next->y = 0.26 * x + 0.24 * y + 0.44;
	color->r = 80;
	color->g = 180;
	color->b = 20;
}
