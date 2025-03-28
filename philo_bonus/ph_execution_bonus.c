/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_execution_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:01 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:46:24 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	fork_failed(pid_t *pids, int i)
{
	if (pids[i] == -1)
	{
		while (--i >= 0)
		{
			kill(pids[i], SIGTERM);
			waitpid(pids[i], NULL, 0);
		}
		return (1);
	}
	return (0);
}

int	launch_phs(t_ph *philos, t_sim *sim)
{
	int	i;

	i = -1;
	sim->start_time = get_current_time();
	while (++i < sim->nphilos)
	{
		sim->pids[i] = fork();
		if (i == 0)
			sim->monitor_pid = sim->pids[i];
		if (fork_failed(sim->pids, i))
			return (-1);
		else if (sim->pids[i] == 0)
			run_ph(&philos[i]);
	}
	if (sim->ntime_must_eat > 0)
	{
		if (pthread_create(&sim->meal_monitor,
				NULL, monitor_meal_completion, sim))
			return (-1);
		pthread_detach(sim->meal_monitor);
	}
	return (terminate_processes(sim));
}

void	release_resources(t_sim *sim)
{
	sem_close(sim->write_sem);
	sem_close(sim->meals_sem);
	sem_close(sim->death_sem);
	sem_close(sim->forks_sem);
	free(sim->pids);
	free(sim->phs_array);
}
