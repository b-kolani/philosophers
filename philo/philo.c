/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:15:38 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:18:22 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_ph *ph, const char *msg)
{
	if (stop_execution(0, ph->sim))
		return (1);
	pthread_mutex_lock(&ph->sim->print_lock);
	printf("%zu %d %s\n", get_time() - ph->sim->start_time, ph->id, msg);
	pthread_mutex_unlock(&ph->sim->print_lock);
	return (0);
}

void	print_global_status(t_sim *sim, const char *msg, int id)
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%zu %d %s\n", get_time() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->print_lock);
}

int	main(int ac, char *av[])
{
	int		status_codes[4];
	t_sim	sim;
	t_ph	*phs;

	phs = NULL;
	if (ac == 5 || ac == 6)
	{
		if (validate_input(&sim, av, ac == 6) == -1)
			return (printf("philo: wrong arguments\n"), 1);
		if (ac == 6 && sim.ntime_must_eat == 0)
			return (0);
		if (manage_locks(&sim, START, status_codes) == -1)
			return (printf("philo: something wrong occurred\n"), 1);
		if (setup_phs(&sim, &phs) == -1)
			return (printf("philo: something wrong occurred\n"), 1);
		if (launch_phs(phs, &sim) == -1)
			return (cleanup_resources(&sim, status_codes, 1), 1);
		cleanup_resources(&sim, status_codes, 1);
		return (0);
	}
	printf("philo: wrong number of arguments\n");
	return (1);
}
