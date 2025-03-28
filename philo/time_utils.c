/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:10:51 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:06:35 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	delay_execution(size_t milliseconds, t_sim *sim)
{
	size_t	start_time;

	start_time = get_time();
	while (milliseconds + start_time > get_time())
	{
		if (stop_execution(0, sim))
			break ;
		usleep(500);
	}
}

int	stop_execution(int signal, t_sim *sim)
{
	static int	terminated;
	int			outcome;

	outcome = 0;
	if (signal == -1)
	{
		pthread_mutex_lock(&sim->stop_lock);
		terminated = 1;
		pthread_mutex_unlock(&sim->stop_lock);
	}
	if (signal == 0)
	{
		pthread_mutex_lock(&sim->stop_lock);
		outcome = terminated;
		pthread_mutex_unlock(&sim->stop_lock);
	}
	return (outcome);
}

int	check_meal_completion(t_ph *phs, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nphilos)
	{
		pthread_mutex_lock(&sim->meals_lock);
		if (phs[i].meals_eaten < sim->ntime_must_eat)
		{
			pthread_mutex_unlock(&sim->meals_lock);
			return (0);
		}
		pthread_mutex_unlock(&sim->meals_lock);
		i++;
	}
	return (1);
}
