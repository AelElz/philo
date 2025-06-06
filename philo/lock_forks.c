/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:00 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 16:17:55 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_single_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (check_simulation_end(philo->input))
		return (0);
	pthread_mutex_lock(fork);
	if (check_simulation_end(philo->input))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	print_action(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (philo->id % 2 != 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	if (!lock_single_fork(philo, first))
		return (0);
	if (philo->input->nbr_philo == 1)
	{
		ft_usleep(philo->input->die_time, philo);
		pthread_mutex_unlock(first);
		return (0);
	}
	if (!lock_single_fork(philo, second))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
