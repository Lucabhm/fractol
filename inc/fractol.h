/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:14:42 by lucabohn          #+#    #+#             */
/*   Updated: 2025/03/10 17:03:54 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libs/ft_libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/mlx/include/MLX42/MLX42.h"

typedef struct s_data
{
	int			type;
	mlx_t		*window_ptr;
	mlx_image_t	*img_ptr;
}				t_data;

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
	char	a;
}				t_color;

void		init_data(char *type, t_data *data);
void		create_fractal(t_data *data);
void		calc_mandelbrot(float real, float imaginary, t_color *color);
uint32_t	create_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		error(int msg, t_data *data);

#endif