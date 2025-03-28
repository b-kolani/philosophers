/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resrcs_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:09:34 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 15:46:06 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_ph_mutexes(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nphilos)
		pthread_mutex_destroy(&((sim->phs_array)[i].right_fork));
}

static void	destroy_sim_mutexes(t_sim *sim, int *status_array)
{
	if (status_array[0] == 0)
		pthread_mutex_destroy(&sim->print_lock);
	if (status_array[1] == 0)
		pthread_mutex_destroy(&sim->meals_lock);
	if (status_array[2] == 0)
		pthread_mutex_destroy(&sim->death_lock);
	if (status_array[3] == 0)
		pthread_mutex_destroy(&sim->stop_lock);
}

void	cleanup_resources(t_sim *sim, int *status_array, int cleanup_flag)
{
	destroy_ph_mutexes(sim);
	destroy_sim_mutexes(sim, status_array);
	if (cleanup_flag)
		free(sim->phs_array);
}
