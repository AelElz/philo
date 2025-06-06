/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azha <ael-azha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:22:34 by ael-azha          #+#    #+#             */
/*   Updated: 2025/06/06 22:15:44 by ael-azha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"

typedef struct s_input
{
	long			nbr_philo;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			count_eat;
	long long		start_time;
	int				is_dead;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_locks;
	pthread_mutex_t	*meals_eaten_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*last_meal_time_locks;
	struct s_philo	*philos;
}					t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*meals_eaten_locks;
	pthread_mutex_t	*last_meal_time_lock;
	long long		last_meal_time;
	int				meals_eaten;
	t_input			*input;
}					t_philo;

// philo_utils.c
int					ft_atoi(char *str, t_input *args);
long				get_current_time(void);
void				free_all(t_input *input);
int					check_simulation_end(t_input *input);
void				ft_usleep(long long time, t_philo *philo);
int					ft_isdigit(int c);
// philo_routine.c
void				*philos_routine(void *arg);
void				eat(t_philo *philo);
void				print_action(t_philo *philo, char *action);
void				handle_one_philosopher(t_philo *philo);
// parse.c
int					check_args(int ac, char **av, t_input *args);
// init.c
int					init_forks(t_input *input);
int					init_philo(t_input *input);
// monitor.c
int					is_all_eat(t_philo *philo);
void				*death_monitor(void *arg);
int					start_simulation(t_input *input);
// routine.c
int					philo_sleep(t_philo *philo);
int					philo_eat(t_philo *philo);
int					philo_think(t_philo *philo);
int					check_philo_died(t_philo *philo);
// lock_forks.c
int					take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
// actions.c

int					philo_died(t_philo *philo);
#endif
