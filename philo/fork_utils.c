/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:09:00 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:06:47 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_left_forks(t_ph *philos, int nphilos)
{
	int	i;

	i = -1;
	while (++i < nphilos)
	{
		if (i == 0)
			philos[i].left_fork = &philos[nphilos - 1].right_fork;
		else
			philos[i].left_fork = &philos[i - 1].right_fork;
	}
}

static void	assign_fork_priorities(t_ph *philos, int nphilos)
{
	int	i;

	i = -1;
	while (++i < nphilos)
	{
		if (philos[i].id % 2 == 0)
		{
			philos[i].primary_fork = philos[i].left_fork;
			philos[i].secondary_fork = &philos[i].right_fork;
		}
		else
		{
			philos[i].primary_fork = &philos[i].right_fork;
			philos[i].secondary_fork = philos[i].left_fork;
		}
	}
}

void	link_forks(t_ph *philos, int nphilos)
{
	assign_left_forks(philos, nphilos);
	assign_fork_priorities(philos, nphilos);
}
