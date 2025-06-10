/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:31 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 16:26:10 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		input->philos[i].last_meal_time = input->start_time;
		if (pthread_create(&input->philos[i].thread, NULL, philos_routine,
				&input->philos[i]) != 0)
			printf("Error: Failed to create philosophers %d\n",
				i + 1);
		i++;
	}
}

int	start_simulation(t_input *input)
{
	pthread_t	monitor;
	int			i;

	create_threads(input);
	if (pthread_create(&monitor, NULL, death_monitor, input) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < input->nbr_philo)
		pthread_join(input->philos[i++].thread, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_input	input;

	memset(&input, 0, sizeof(t_input));
	if (!check_args(ac, av, &input))
		return (1);
	if (init_forks(&input) || init_philo(&input))
	{
		printf("Error: Init failed\n");
		free_all(&input);
		return (1);
	}
	if (input.count_eat != 0)
		start_simulation(&input);
	free_all(&input);
	return (0);
}
