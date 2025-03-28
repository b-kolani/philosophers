/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:22:14 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 18:55:54 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	remove_all_semaphores(char **sem_names, int flag)
{
	sem_unlink(sem_names[0]);
	sem_unlink(sem_names[1]);
	sem_unlink(sem_names[2]);
	sem_unlink(sem_names[3]);
	sem_unlink(sem_names[4]);
	if (flag)
		free(sem_names);
}

static int	close_semaphores(t_sim *sim, int stage)
{
	if (stage == 1)
		sem_close(sim->forks_sem);
	else if (stage == 2)
	{
		sem_close(sim->forks_sem);
		sem_close(sim->write_sem);
	}
	else if (stage == 3)
	{
		sem_close(sim->forks_sem);
		sem_close(sim->write_sem);
		sem_close(sim->death_sem);
	}
	else if (stage == 4)
	{
		sem_close(sim->forks_sem);
		sem_close(sim->write_sem);
		sem_close(sim->death_sem);
		sem_close(sim->meals_sem);
	}
	while (--stage)
		sem_unlink(sim->sem_names[stage]);
	return (-1);
}

static void	init_sem_names(t_sim *sim)
{
	sim->sem_names[0] = "/forks_sem";
	sim->sem_names[1] = "/write_sem";
	sim->sem_names[2] = "/death_sem";
	sim->sem_names[3] = "/meals_sem";
	sim->sem_names[4] = "/resrcs_sem";
}

int	initialize_semaphores(t_sim *sim, int nphilos)
{
	sim->sem_names = malloc(5 * sizeof(char *));
	if (!sim->sem_names)
		return (printf("philo_bonus: allocation failed"));
	init_sem_names(sim);
	remove_all_semaphores(sim->sem_names, 0);
	sim->forks_sem = sem_open(sim->sem_names[0], O_CREAT, 0644, nphilos);
	if (sim->forks_sem == SEM_FAILED)
		return (-1);
	sim->write_sem = sem_open(sim->sem_names[1], O_CREAT, 0644, 1);
	if (sim->write_sem == SEM_FAILED)
		return (close_semaphores(sim, 1));
	sim->death_sem = sem_open(sim->sem_names[2], O_CREAT, 0644, 1);
	if (sim->death_sem == SEM_FAILED)
		return (close_semaphores(sim, 2));
	sim->meals_sem = sem_open(sim->sem_names[3], O_CREAT, 0644, 0);
	if (sim->meals_sem == SEM_FAILED)
		return (close_semaphores(sim, 3));
	sim->resrcs_sem = sem_open(sim->sem_names[4], O_CREAT, 0644, 0);
	if (sim->resrcs_sem == SEM_FAILED)
		return (close_semaphores(sim, 4));
	remove_all_semaphores(sim->sem_names, 1);
	return (0);
}
