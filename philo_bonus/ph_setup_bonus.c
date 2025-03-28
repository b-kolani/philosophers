/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_setup_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:23:19 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:53:27 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validate_arguments(t_sim *sim, char **args, int has_meal_limit)
{
	int	error;

	error = 0;
	sim->nphilos = ft_atoi(args[1], &error);
	sim->death_time = ft_atoi(args[2], &error);
	sim->time_to_eat = ft_atoi(args[3], &error);
	sim->time_to_sleep = ft_atoi(args[4], &error);
	sim->ntime_must_eat = -1;
	if (has_meal_limit)
		sim->ntime_must_eat = ft_atoi(args[5], &error);
	if (error || sim->death_time <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0
		|| (has_meal_limit && sim->ntime_must_eat < 0))
		return (-1);
	sim->pids = malloc(sizeof(pid_t) * sim->nphilos);
	if (sim->pids == NULL)
		return (-1);
	return (0);
}

int	setup_phs(t_sim *sim, t_ph **philo_ptr)
{
	t_ph	*philos;
	int		i;

	philos = malloc(sizeof(t_ph) * sim->nphilos);
	i = -1;
	if (philos == NULL)
		return (-1);
	while (++i < sim->nphilos)
	{
		philos[i].id = i + 1;
		philos[i].sim = sim;
	}
	sim->phs_array = philos;
	*philo_ptr = philos;
	return (0);
}

void	*monitor_meal_completion(void *sim_ptr)
{
	t_sim	*sim;
	int		i;

	sim = sim_ptr;
	i = -1;
	while (++i < sim->nphilos)
		sem_wait(sim->meals_sem);
	kill(sim->monitor_pid, SIGTERM);
	return (NULL);
}

int	terminate_processes(t_sim *sim)
{
	int	i;
	int	status;

	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM)
	{
		i = 0;
		while (++i < sim->nphilos)
			kill(sim->pids[i], SIGTERM);
	}
	else
	{
		i = -1;
		while (++i < sim->nphilos)
			kill(sim->pids[i], SIGTERM);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}
