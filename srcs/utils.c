/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:05:35 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/11 13:48:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

float	ft_atof(char *input)
{
	float	result;
	int		sign;

	result = 0.0;
	sign = 1;
	if (!check_input(input))
		error(1, NULL);
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	if (*input == '-')
		sign = -1;
	if (*input == '-' || *input == '+')
		input++;
	extract_float(&result, input);
	return (sign * result);
}

void	extract_float(float *result, char *input)
{
	float	fraction;
	bool	after;

	fraction = 0.1;
	after = false;
	while (*input)
	{
		if (*input == '.')
		{
			after = true;
			input++;
		}
		if (!ft_isdigit(*input))
			break ;
		if (!after)
			*result += *result * 10 + (*input - '0');
		else
		{
			*result += (*input - '0') * fraction;
			fraction *= 0.1;
		}
		input++;
	}
}

bool	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (false);
	while (input[i])
	{
		if (input[i] != '-' && input[i] != '+'
			&& !ft_isdigit(input[i]) && input[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

void	check_type(int size, char **argv, t_data *data)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len == 10 || len == 5 || len == 4)
	{
		if (!ft_strncmp(argv[1], "Mandelbrot", len) && size == 2)
			data->type = 0;
		else if (!ft_strncmp(argv[1], "Julia", len) && size == 4)
		{
			data->type = 1;
			data->zr = ft_atof(argv[2]);
			data->zi = ft_atof(argv[3]);
		}
		else if (!ft_strncmp(argv[1], "Fern", len) && size == 2)
			data->type = 2;
		else
			error(2, NULL);
	}
	else
		error(2, NULL);
}

void	get_coord_size(t_data *data)
{
	if (data->type != 2)
	{
		data->x_max = 2.0;
		data->x_min = -2.0;
		data->y_max = 2.0;
		data->y_min = -2.0;
	}
	else
	{
		data->x_max = 5.0;
		data->x_min = -5.0;
		data->y_max = 0.0;
		data->y_min = -12.0;
	}
}
