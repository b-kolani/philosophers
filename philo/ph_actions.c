/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:06:27 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:18:08 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_forks(t_ph *ph)
{
	if (ph->sim->nphilos == 1)
	{
		while (!stop_execution(0, ph->sim))
			usleep(1000);
		pthread_mutex_unlock(ph->primary_fork);
		return (0);
	}
	if (stop_execution(0, ph->sim))
	{
		pthread_mutex_unlock(ph->primary_fork);
		return (0);
	}
	pthread_mutex_lock(ph->secondary_fork);
	if (print_status(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(ph->primary_fork);
		pthread_mutex_unlock(ph->secondary_fork);
		return (0);
	}
	return (1);
}

int	eat_and_release(t_ph *ph)
{
	pthread_mutex_lock(&ph->sim->death_lock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->sim->death_lock);
	if (print_status(ph, "is eating"))
	{
		pthread_mutex_unlock(ph->primary_fork);
		pthread_mutex_unlock(ph->secondary_fork);
		return (0);
	}
	delay_execution(ph->sim->time_to_eat, ph->sim);
	pthread_mutex_unlock(ph->secondary_fork);
	pthread_mutex_unlock(ph->primary_fork);
	pthread_mutex_lock(&ph->sim->meals_lock);
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->sim->meals_lock);
	return (1);
}

int	perform_eat(t_ph *ph)
{
	pthread_mutex_lock(ph->primary_fork);
	if (print_status(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(ph->primary_fork);
		return (0);
	}
	if (!acquire_forks(ph))
		return (0);
	return (eat_and_release(ph));
}

int	perform_think(t_ph *ph)
{
	if (print_status(ph, "is thinking"))
		return (0);
	return (1);
}

int	perform_sleep(t_ph *ph)
{
	if (print_status(ph, "is sleeping"))
		return (0);
	delay_execution(ph->sim->time_to_sleep, ph->sim);
	return (1);
}
