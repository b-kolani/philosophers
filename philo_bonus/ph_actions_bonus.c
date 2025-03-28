/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:29 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:46:24 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_message(t_ph *philo, char *msg)
{
	sem_wait(philo->sim->write_sem);
	printf("%zu %d %s\n",
		get_current_time() - philo->sim->start_time, philo->id, msg);
	sem_post(philo->sim->write_sem);
}

static void	perform_eating(t_ph *philo, int *meal_posted)
{
	if (philo->id % 2 == 0)
		sem_wait(philo->sim->resrcs_sem);
	sem_wait(philo->sim->forks_sem);
	print_message(philo, "has taken a fork");
	sem_wait(philo->sim->forks_sem);
	print_message(philo, "has taken a fork");
	sem_wait(philo->sim->death_sem);
	philo->last_meal = get_current_time();
	sem_post(philo->sim->death_sem);
	if (philo->id % 2)
		sem_post(philo->sim->resrcs_sem);
	print_message(philo, "is eating");
	delay_execution(philo->sim->time_to_eat);
	sem_post(philo->sim->forks_sem);
	sem_post(philo->sim->forks_sem);
	philo->meals_count++;
	if (philo->sim->ntime_must_eat > 0
		&& philo->meals_count >= philo->sim->ntime_must_eat && !*meal_posted)
	{
		sem_post(philo->sim->meals_sem);
		*meal_posted = 1;
	}
}

static void	*check_for_death(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	while (1)
	{
		sem_wait(philo->sim->death_sem);
		if (get_current_time() - philo->last_meal > philo->sim->death_time)
		{
			sem_wait(philo->sim->write_sem);
			printf("%zu %d died\n",
				get_current_time() - philo->sim->start_time, philo->id);
			exit(0);
		}
		sem_post(philo->sim->death_sem);
	}
	return (NULL);
}

void	run_ph(t_ph *philo)
{
	pthread_t	death_monitor_thread;
	int			meal_posted;

	meal_posted = 0;
	philo->last_meal = get_current_time();
	if (pthread_create(&death_monitor_thread, NULL, check_for_death, philo))
		exit(1);
	pthread_detach(death_monitor_thread);
	while (1)
	{
		perform_eating(philo, &meal_posted);
		print_message(philo, "is sleeping");
		delay_execution(philo->sim->time_to_sleep);
		print_message(philo, "is thinking");
	}
}
