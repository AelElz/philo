/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:21:56 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 22:16:14 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutexes_allocate(t_input *input)
{
	input->forks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	input->meal_locks = malloc(sizeof(pthread_mutex_t) * input->nbr_philo);
	input->meals_eaten_locks = malloc(sizeof(pthread_mutex_t)
			* input->nbr_philo);
	input->last_meal_time_locks = malloc(sizeof(pthread_mutex_t)
			* input->nbr_philo);
	if (!input->forks || !input->meal_locks
		|| !input->meals_eaten_locks || !input->last_meal_time_locks)
		return (1);
	return (0);
}

int	init_forks(t_input *input)
{
	int	i;

	if (mutexes_allocate(input))
		return (1);
	i = 0;
	while (i < input->nbr_philo)
	{
		if (pthread_mutex_init(&input->last_meal_time_locks[i], NULL)
			|| pthread_mutex_init(&input->forks[i], NULL)
			|| pthread_mutex_init(&input->meal_locks[i], NULL)
			|| pthread_mutex_init(&input->meals_eaten_locks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&input->print_lock, NULL)
		|| pthread_mutex_init(&input->death_lock, NULL))
		return (1);
	return (0);
}

int	init_philo(t_input *input)
{
	int		i;
	t_philo	*philo;

	input->philos = malloc(sizeof(t_philo) * input->nbr_philo);
	if (!input->philos)
		return (1);
	input->start_time = get_current_time();
	input->is_dead = 0;
	i = 0;
	while (i < input->nbr_philo)
	{
		philo = &input->philos[i];
		philo->id = i + 1;
		philo->input = input;
		philo->meals_eaten = 0;
		philo->last_meal_time = input->start_time;
		philo->left_fork = &input->forks[i];
		philo->right_fork = &input->forks[(i + 1) % input->nbr_philo];
		input->philos[i].last_meal_time_lock = &input->last_meal_time_locks[i];
		philo->meal_lock = &input->meal_locks[i];
		i++;
	}
	return (0);
}
