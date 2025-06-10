/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:13 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 22:15:55 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_and_handle_death(t_input *input, t_philo *philo)
{
	if (philo_died(philo))
	{
		pthread_mutex_lock(&input->death_lock);
		input->is_dead = 1;
		pthread_mutex_unlock(&input->death_lock);
		pthread_mutex_lock(&input->print_lock);
		printf(RED"[%lld]"RESET" %d died\n",
			get_current_time() - input->start_time, philo->id);
		pthread_mutex_unlock(&input->print_lock);
		return (1);
	}
	return (0);
}

static int	philos_running(t_input *input)
{
	int	i;
	int	philos_done;

	i = 0;
	philos_done = 0;
	while (i < input->nbr_philo)
	{
		if (is_all_eat(&input->philos[i]))
			philos_done++;
		else if (check_and_handle_death(input, &input->philos[i]))
			return (0);
		i++;
	}
	if (philos_done == input->nbr_philo)
		return (0);
	return (1);
}

void	*death_monitor(void *arg)
{
	t_input	*input;

	input = (t_input *)arg;
	while (get_current_time() < input->start_time)
		usleep(250);
	usleep(input->die_time * 1000);
	while (philos_running(input))
		usleep(500);
	return (NULL);
}
