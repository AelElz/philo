/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:21:51 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 22:06:46 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	int			dead;
	long long	now;

	now = get_current_time();
	pthread_mutex_lock(philo->last_meal_time_lock);
	dead = (now - philo->last_meal_time > philo->input->die_time);
	pthread_mutex_unlock(philo->last_meal_time_lock);
	return (dead);
}

int	is_all_eat(t_philo *philo)
{
	int	nb_iterations;
	int	done;

	nb_iterations = philo->input->count_eat;
	if (nb_iterations < 0)
		return (0);
	pthread_mutex_lock(philo->meal_lock);
	done = (philo->meals_eaten >= nb_iterations);
	pthread_mutex_unlock(philo->meal_lock);
	return (done);
}

int	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	if (check_simulation_end(philo->input) || philo_died(philo))
	{
		release_forks(philo);
		return (0);
	}
	print_action(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->input->eat_time, philo);
	pthread_mutex_lock(philo->last_meal_time_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->last_meal_time_lock);
	release_forks(philo);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (check_simulation_end(philo->input))
		return (0);
	print_action(philo, "is sleeping");
	ft_usleep(philo->input->sleep_time, philo);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (check_simulation_end(philo->input) || philo_died(philo))
		return (0);
	print_action(philo, "is thinking");
	return (1);
}
