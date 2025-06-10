/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:20 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/10 17:09:41 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->input->print_lock);
	if (check_simulation_end(philo->input))
	{
		pthread_mutex_unlock(&philo->input->print_lock);
		return ;
	}
	printf(GREEN"[%lld]"RESET" %d %s\n",
		get_current_time() - philo->input->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->input->print_lock);
}

void	handle_one_philosopher(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	ft_usleep(philo->input->die_time, philo);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->input->nbr_philo == 1)
	{
		handle_one_philosopher(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(500);
		if (philo->input->nbr_philo < 100)
			usleep(200);
		if (!philo_eat(philo))
			break ;
		if (is_all_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}
