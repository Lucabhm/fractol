/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fern_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:02:08 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 14:06:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	transform(double *x, double *y)
{
	double	random_nbr;
	t_vec2	next;

	random_nbr = (double)rand() / RAND_MAX;
	if (random_nbr < 0.01)
		fern_stem(&next, *y);
	else if (random_nbr < 0.86)
	{
		next_x = 0.85 * (*x) + 0.04 * (*y);
		next_y = -0.04 * (*x) + 0.85 * (*y) + 1.6;
	}
	else if (random_nbr < 0.93)
	{
		next_x = 0.2 * (*x) - 0.26 * (*y);
		next_y = 0.23 * (*x) + 0.22 * (*y) + 1.6;
	}
	else
	{
		next_x = -0.15 * (*x) + 0.28 * (*y);
		next_y = 0.26 * (*x) + 0.24 * (*y) + 0.44;
	}
	*x = next_x;
	*y = next_y;
}

void	fern_stem(t_vec2 *next, double y, t_color *color)
{
	next->x = 0.0;
	next->y = 0.16 * y;
	color->r = 
}
