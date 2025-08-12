/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:08:50 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/12 22:41:14 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_finished(t_table *table)
{
	int	i;
	int	all_finished;

	if (table->must_eat_count <= 0)
		return (0);
	pthread_mutex_lock(&table->death_mutex);
	i = 0;
	all_finished = 1;
	while (i < table->philo_count)
	{
		if (table->philos[i].eat_count < table->must_eat_count)
		{
			all_finished = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (all_finished);
}

int	check_philo_death(t_table *table, int i)
{
	long	current_time;
	int		dead;

	dead = 0;
	current_time = get_time();
	pthread_mutex_lock(&table->death_mutex);
	if (current_time - table->philos[i].last_meal_time > table->time_to_die)
	{
		dead = set_simulation_end(table);
	}
	pthread_mutex_unlock(&table->death_mutex);
	if (dead)
		mutex_print(table, table->philos[i].id, DIED);
	return (dead);
}

void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!is_simulation_end(table))
	{
		if (check_all_finished(table))
		{
			set_simulation_end(table);
			break ;
		}
		i = 0;
		while (i < table->philo_count)
		{
			if (check_philo_death(table, i))
				return (NULL);
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}
