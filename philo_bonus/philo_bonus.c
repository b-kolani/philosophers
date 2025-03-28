/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:27:58 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:43:31 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	t_sim	sim;
	t_ph	*philos;

	memset(&sim, 0, sizeof(sim));
	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (validate_arguments(&sim, av, ac == 6) == -1)
			return (printf("philo_bonus: wrong arguments\n"), 1);
		if (ac == 6 && sim.ntime_must_eat == 0)
			return (0);
		if (initialize_semaphores(&sim, sim.nphilos) == -1)
			return (printf("philo_bonus: something wrong occurred\n"),
				free(sim.pids), 1);
		if (setup_phs(&sim, &philos) == -1)
			return (printf("philo_bonus: something wrong occurred\n"),
				free(sim.pids), 1);
		if (launch_phs(philos, &sim) == -1)
			return (release_resources(&sim), 1);
		release_resources(&sim);
		return (0);
	}
	printf("philo_bonus: wrong arguments number\n");
	return (1);
}
