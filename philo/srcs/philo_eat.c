/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:09:43 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/20 23:18:08 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_fork_priority(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		philo->first = philo->left_fork;
		philo->second = philo->right_fork;
	}
	else
	{
		philo->first = philo->right_fork;
		philo->second = philo->left_fork;
	}
	if (philo->id == philo->table->philo_count)
	{
		if (philo->id % 2 == 1)
		{
			philo->first = philo->right_fork;
			philo->second = philo->left_fork;
		}
		else
		{
			philo->first = philo->left_fork;
			philo->second = philo->right_fork;
		}
	}
}

int	get_fork_algo(t_philo *philo)
{
	t_fork	*f1;
	t_fork	*f2;

	if (is_simulation_end(philo->table))
		return (0);
	get_fork_priority(philo);
	f1 = philo->first;
	f2 = philo->second;
	pthread_mutex_lock(&f1->mutex);
	if (is_simulation_end(philo->table))
	{
		pthread_mutex_unlock(&f1->mutex);
		return (0);
	}
	mutex_print(philo->table, philo->id, TAKE_FORKS);
	pthread_mutex_lock(&f2->mutex);
	if (is_simulation_end(philo->table))
	{
		pthread_mutex_unlock(&f2->mutex);
		pthread_mutex_unlock(&f1->mutex);
		return (0);
	}
	mutex_print(philo->table, philo->id, TAKE_FORKS);
	return (1);
}

void	release_forks(t_philo *philo)
{
	t_fork	*f1;
	t_fork	*f2;

	get_fork_priority(philo);
	f1 = philo->first;
	f2 = philo->second;
	pthread_mutex_unlock(&f2->mutex);
	pthread_mutex_unlock(&f1->mutex);
}

void	philo_eat(t_philo *philo)
{
	if (!get_fork_algo(philo))
		return ;
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->death_mutex);
	mutex_print(philo->table, philo->id, EATING);
	ft_usleep(philo->table->time_to_eat * 1000);
	release_forks(philo);
}
