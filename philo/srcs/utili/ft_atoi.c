/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:09:48 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/18 20:40:01 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	ft_atoi64(const char *str)
{
	int		sign;
	int64_t	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (INT64_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (INT64_MAX);
			return (INT64_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
