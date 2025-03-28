/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:10:24 by bkolani           #+#    #+#             */
/*   Updated: 2025/03/24 16:11:22 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*skip_whitespace(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return (str);
}

static size_t	handle_sign(char **str, int *error_flag)
{
	size_t	result;

	result = 0;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*error_flag = 1;
		(*str)++;
	}
	return (result);
}

static size_t	process_digits(char *str, int *error_flag, size_t result)
{
	while (*str)
	{
		if (result > SIZE_MAX / 10
			|| (result == SIZE_MAX / 10
				&& (size_t)(*str - '0') > SIZE_MAX % 10))
			*error_flag = 1;
		if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str - '0');
		else
			*error_flag = 1;
		str++;
	}
	return (result);
}

size_t	ft_atoi(char *str, int *error_flag)
{
	size_t	result;

	result = 0;
	str = skip_whitespace(str);
	result = handle_sign(&str, error_flag);
	if (!*str)
		*error_flag = 1;
	return (process_digits(str, error_flag, result));
}
