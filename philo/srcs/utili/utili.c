/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utili.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:01:00 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/18 20:40:29 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	mutex_print(t_table *table, int id, char *action)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d %s\n", get_time() - table->start_time, id, action);
	pthread_mutex_unlock(&table->print_mutex);
}

int	is_simulation_end(t_table *table)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&table->death_mutex);
	end = table->simulation_end;
	pthread_mutex_unlock(&table->death_mutex);
	return (end);
}

int	set_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->simulation_end = 1;
	pthread_mutex_unlock(&table->death_mutex);
	return (1);
}
