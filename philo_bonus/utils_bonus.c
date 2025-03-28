/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:26:01 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 19:00:11 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_atoi(char *str, int *error_flag)
{
	size_t	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*error_flag = 1;
		str++;
	}
	if (!*str)
		*error_flag = 1;
	while (*str)
	{
		if (num > SIZE_MAX / 10
			|| (num == SIZE_MAX / 10 && (size_t)(*str - '0') > SIZE_MAX % 10))
			*error_flag = 1;
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			*error_flag = 1;
		str++;
	}
	return (num);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	delay_execution(size_t milliseconds)
{
	size_t	start_time;

	start_time = get_current_time();
	while (milliseconds + start_time > get_current_time())
		usleep(500);
}
