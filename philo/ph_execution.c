/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:07:07 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 17:54:05 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ph_routine(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	while (1)
	{
		if (stop_execution(0, ph->sim))
			break ;
		if (!perform_eat(ph))
			break ;
		if (!perform_sleep(ph))
			break ;
		if (!perform_think(ph))
			break ;
	}
	return (NULL);
}

static void	*monitor(void *arg)
{
	int		i;
	t_sim	*sim;
	t_ph	*phs;

	sim = arg;
	phs = sim->phs_array;
	while (1)
	{
		i = -1;
		while (++i < sim->nphilos)
		{
			pthread_mutex_lock(&sim->death_lock);
			if (get_time() - phs[i].last_meal > sim->time_to_die)
			{
				stop_execution(-1, sim);
				pthread_mutex_unlock(&sim->death_lock);
				print_global_status(sim, "died", phs[i].id);
				return (NULL);
			}
			pthread_mutex_unlock(&sim->death_lock);
		}
		if (sim->ntime_must_eat > 0 && check_meal_completion(phs, sim))
			return (stop_execution(-1, sim), NULL);
	}
	return (NULL);
}

int	launch_phs(t_ph *phs, t_sim *sim)
{
	int	i;

	i = -1;
	sim->start_time = get_time();
	while (++i < sim->nphilos)
	{
		pthread_mutex_lock(&phs[i].sim->meals_lock);
		phs[i].last_meal = get_time();
		pthread_mutex_unlock(&phs[i].sim->meals_lock);
		if (pthread_create(&phs[i].tid, NULL,
				ph_routine, &phs[i]))
		{
			while (--i)
				pthread_detach(phs[i].tid);
			return (-1);
		}
	}
	usleep(1000);
	monitor(sim);
	i = -1;
	while (++i < sim->nphilos)
		pthread_join(phs[i].tid, NULL);
	return (0);
}
