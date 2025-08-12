/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:22:16 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/12 22:40:15 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_table *table)
{
	int64_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->forks[i].id = i;
		table->forks[i].available = 1;
		table->forks[i].last_used = -1;
		if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
		{
			ft_fputs("Error: fork mutex init failed\n", STDERR_FILENO);
			return ;
		}
		i++;
	}
}

void	init_philo(t_table *table)
{
	int64_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->philo_count];
		table->philos[i].table = table;
		i++;
	}
}
