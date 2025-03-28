/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:12:18 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:07:18 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TERMINATE -1
# define START 1

typedef struct s_ph	t_ph;

typedef struct s_sim
{
	int				time_to_eat;
	int				time_to_sleep;
	int				nphilos;
	int				ntime_must_eat;
	size_t			time_to_die;
	size_t			start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	stop_lock;
	t_ph			*phs_array;
}	t_sim;

typedef struct s_ph
{
	int				meals_eaten;
	int				id;
	t_sim			*sim;
	size_t			last_meal;
	pthread_t		tid;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*primary_fork;
	pthread_mutex_t	*secondary_fork;
}	t_ph;

size_t	get_time(void);
size_t	ft_atoi(char *str, int *error_flag);
int		stop_execution(int signal, t_sim *sim);
void	delay_execution(size_t milliseconds, t_sim *sim);
void	cleanup_resources(t_sim *sim, int *status_array, int cleanup_flag);
int		validate_input(t_sim *state, char **args, int has_optional);
int		manage_locks(t_sim *sim, int operation, int *lock_status);
int		setup_phs(t_sim *sim, t_ph **phs);
void	link_forks(t_ph *phs, int nphilos);
int		print_status(t_ph *ph, const char *msg);
void	print_global_status(t_sim *sim, const char *msg, int id);
int		perform_eat(t_ph *ph);
int		perform_think(t_ph *ph);
int		perform_sleep(t_ph *ph);
int		launch_phs(t_ph *phs, t_sim *sim);
int		check_meal_completion(t_ph *phs, t_sim *sim);

#endif