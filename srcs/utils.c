/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:05:35 by lbohm             #+#    #+#             */
/*   Updated: 2025/09/10 15:44:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

float	ft_atof(char *input)
{
	float	result;
	float	fraction;
	int		sign;
	bool	after;

	result = 0.0;
	sign = 1;
	after = false;
	fraction = 0.1;

	if (!check_input(input))
		error(1, NULL);

	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	if (*input == '-')
		sign = -1;
	if (*input == '-' || *input == '+')
		input++;
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
			result += result * 10 + (*input - '0');
		else
		{
			result += (*input - '0') * fraction;
			fraction *= 0.1;
		}
		input++;
	}
	return (sign * result);
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
