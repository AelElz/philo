/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:24 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 18:09:53 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	handle_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	is_overflow(long result, int sign, t_input *args)
{
	if ((result * sign) > 2147483647 || (result * sign) < -2147483648)
	{
		args->flag = 1;
		return (1);
	}
	return (0);
}

int	ft_atoi(char *str, t_input *args)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	args->flag = 0;
	while (is_space(str[i]))
		i++;
	sign = handle_sign(str, &i);
	if (!str[i])
		return (args->flag = 1, -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (is_overflow(result, sign, args))
			return (-1);
		i++;
	}
	if (str[i] != '\0')
	{
		args->flag = 1;
		return (-1);
	}
	return ((int)(result * sign));
}
