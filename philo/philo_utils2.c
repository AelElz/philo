/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:27 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 21:35:32 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_simulation_end(t_input *input)
{
	int	end;

	pthread_mutex_lock(&input->death_lock);
	end = input->is_dead;
	pthread_mutex_unlock(&input->death_lock);
	return (end);
}

int	check_argument(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		if (check_simulation_end(philo->input))
			break ;
		usleep(100);
	}
}

void	free_all(t_input *input)
{
	int	i;

	if (!input)
		return ;
	if (input->philos)
		free(input->philos);
	if (input->forks && input->meal_locks
		&& input->meals_eaten_locks && input->last_meal_time_locks)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			pthread_mutex_destroy(&input->forks[i]);
			pthread_mutex_destroy(&input->meal_locks[i]);
			pthread_mutex_destroy(&input->meals_eaten_locks[i]);
			pthread_mutex_destroy(&input->last_meal_time_locks[i]);
			i++;
		}
		free(input->forks);
		free(input->meal_locks);
		free(input->meals_eaten_locks);
		free(input->last_meal_time_locks);
	}
	pthread_mutex_destroy(&input->print_lock);
	pthread_mutex_destroy(&input->death_lock);
}
