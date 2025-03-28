/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:36 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:08:54 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_failed_init(t_sim *sim, t_ph *phs, int start_idx)
{
	while (--start_idx > -1)
		pthread_mutex_destroy(&phs[start_idx].right_fork);
	manage_locks(sim, TERMINATE, NULL);
	free(phs);
}

static int	init_ph_mutexes(t_sim *sim, t_ph *phs)
{
	int	i;

	i = -1;
	while (++i < sim->nphilos)
	{
		if (pthread_mutex_init(&phs[i].right_fork, NULL))
		{
			cleanup_failed_init(sim, phs, i);
			return (-1);
		}
		phs[i].id = i + 1;
		phs[i].sim = sim;
	}
	return (0);
}

int	setup_phs(t_sim *sim, t_ph **phs_arr)
{
	t_ph	*phs;

	phs = malloc(sizeof(t_ph) * sim->nphilos);
	if (phs == NULL)
		return (-1);
	*phs_arr = phs;
	if (init_ph_mutexes(sim, phs) == -1)
		return (-1);
	sim->phs_array = phs;
	link_forks(phs, sim->nphilos);
	return (0);
}
