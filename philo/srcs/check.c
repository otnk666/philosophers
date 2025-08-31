/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:49:58 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/31 15:13:35 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_contains_non_digits(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (error_msg("Error", NULL,
					"Arguments must be positive integers"));
		}
		i++;
	}
	return (0);
}

int	is_overflow_int64(int64_t value, char *str)
{
	if (value == INT64_MAX)
	{
		if (ft_strcmp(str, "9223372036854775807") != 0)
			return (1);
	}
	else if (value == INT64_MIN)
	{
		if (ft_strcmp(str, "-9223372036854775808") != 0)
			return (1);
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	int		i;
	int64_t	value;

	if (ac != 5 && ac != 6)
	{
		return (error_usage("./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"));
	}
	i = 1;
	while (i < ac)
	{
		if (is_contains_non_digits(av[i]))
			return (error_error("Arguments must be positive integers"));
		value = ft_atoi64(av[i]);
		if (value <= 0)
			return (error_error("Arguments must be at least 1"));
		if (is_overflow_int64(value, av[i]))
			return (error_error("Arguments exceed maximum allowed value"));
		i++;
	}
	return (0);
}
