/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:07:52 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/18 20:03:45 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	mutex_print(philo->table, philo->id, THINKING);
	ft_usleep(100);
}

void	philo_sleep(t_philo *philo)
{
	mutex_print(philo->table, philo->id, SLEEPING);
	ft_usleep(philo->table->time_to_sleep * 1000);
}

int	check_continue(t_philo *philo)
{
	int	count;

	if (is_simulation_end(philo->table))
		return (0);
	if (philo->table->must_eat_count != -1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->death_mutex);
			return (0);
		}
		count = philo->eat_count;
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (count >= philo->table->must_eat_count)
			return (0);
	}
	return (1);
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->death_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (check_continue(philo))
	{
		philo_think(philo);
		if (!check_continue(philo))
			break ;
		philo_eat(philo);
		if (!check_continue(philo))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
