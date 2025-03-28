/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:21:13 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:50:01 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include "fcntl.h"
# include "string.h"

typedef struct s_ph	t_ph;

typedef struct s_sim
{
	int			time_to_eat;
	int			time_to_sleep;
	int			nphilos;
	int			ntime_must_eat;
	size_t		death_time;
	size_t		start_time;
	pid_t		*pids;
	pid_t		monitor_pid;
	pthread_t	meal_monitor;
	sem_t		*forks_sem;
	sem_t		*write_sem;
	sem_t		*death_sem;
	sem_t		*meals_sem;
	sem_t		*resrcs_sem;
	char		**sem_names;
	t_ph		*phs_array;
}	t_sim;

typedef struct s_ph
{
	int		id;
	int		meals_count;
	size_t	last_meal;
	t_sim	*sim;
}	t_ph;

int		initialize_semaphores(t_sim *sim, int nphilos);
int		validate_arguments(t_sim *sim, char **args, int has_meal_limit);
int		setup_phs(t_sim *sim, t_ph **philo_ptr);
void	*monitor_meal_completion(void *sim_ptr);
int		terminate_processes(t_sim *sim);
int		launch_phs(t_ph *philos, t_sim *sim);
void	release_resources(t_sim *sim);
void	run_ph(t_ph *philo);
size_t	ft_atoi(char *str, int *error_flag);
size_t	get_current_time(void);
void	delay_execution(size_t milliseconds);

#endif