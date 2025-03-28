/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:05 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:01:26 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_locks(t_sim *sim, int *lock_status)
{
	lock_status[0] = pthread_mutex_init(&sim->print_lock, NULL);
	if (lock_status[0] != 0)
		return (-1);
	lock_status[1] = pthread_mutex_init(&sim->meals_lock, NULL);
	lock_status[2] = pthread_mutex_init(&sim->death_lock, NULL);
	lock_status[3] = pthread_mutex_init(&sim->stop_lock, NULL);
	if (lock_status[0] != 0 || lock_status[1] != 0
		|| lock_status[2] != 0 || lock_status[3] != 0)
	{
		cleanup_resources(sim, lock_status, 0);
		return (-1);
	}
	return (0);
}

static int	terminate_locks(t_sim *sim)
{
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->meals_lock);
	pthread_mutex_destroy(&sim->death_lock);
	pthread_mutex_destroy(&sim->stop_lock);
	return (0);
}

int	manage_locks(t_sim *sim, int operation, int *lock_status)
{
	if (operation == START)
		return (initialize_locks(sim, lock_status));
	if (operation == TERMINATE)
		return (terminate_locks(sim));
	return (0);
}

int	validate_input(t_sim *sim, char **av, int has_optional)
{
	int	error_flag;

	error_flag = 0;
	sim->nphilos = ft_atoi(av[1], &error_flag);
	sim->time_to_die = ft_atoi(av[2], &error_flag);
	sim->time_to_eat = ft_atoi(av[3], &error_flag);
	sim->time_to_sleep = ft_atoi(av[4], &error_flag);
	sim->ntime_must_eat = -1;
	if (has_optional)
		sim->ntime_must_eat = ft_atoi(av[5], &error_flag);
	if (error_flag || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| (has_optional && sim->ntime_must_eat < 0))
		return (-1);
	return (0);
}
