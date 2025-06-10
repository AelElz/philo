/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:17 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 18:10:29 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_digit(av[i]))
		{
			printf("Error: Argument %d is not a valid: %s\n", i, av[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_args_values(t_input *args, int ac)
{
	if (args->nbr_philo <= 0)
		return (printf("Error: Number of philos must be greater than 0\n"), 0);
	if (args->die_time <= 0)
		return (printf("Error: Time to die must be greater than 0\n"), 0);
	if (args->eat_time <= 0)
		return (printf("Error: Time to eat must be greater than 0\n"), 0);
	if (args->sleep_time <= 0)
		return (printf("Error: Time to sleep must be greater than 0\n"), 0);
	if (ac == 6 && args->count_eat < 0)
		return (printf("Error: Must eat count must be >= 0\n"), 0);
	return (1);
}

int	check_args(int ac, char **av, t_input *args)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Incorrect number of arguments\n"), 0);
	if (!validate_args(ac, av))
		return (0);
	args->nbr_philo = ft_atoi(av[1], args);
	args->die_time = ft_atoi(av[2], args);
	args->eat_time = ft_atoi(av[3], args);
	args->sleep_time = ft_atoi(av[4], args);
	if (ac == 6)
		args->count_eat = ft_atoi(av[5], args);
	else
		args->count_eat = -1;
	if (!validate_args_values(args, ac))
		return (0);
	return (1);
}
