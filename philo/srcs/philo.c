/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:07:52 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/20 23:24:26 by skomatsu         ###   ########.fr       */
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

int	can_eat_more(t_philo *philo)
{
	int	eat_count;
	int	must_count;

	pthread_mutex_lock(&philo->table->death_mutex);
	eat_count = philo->eat_count;
	must_count = philo->table->must_eat_count;
	pthread_mutex_unlock(&philo->table->death_mutex);
	if (must_count == -1)
		return (1);
	if (eat_count < must_count)
		return (1);
	return (0);
}

void	think_wait_death(t_philo *philo)
{
	while (!is_simulation_end(philo->table))
		ft_usleep(10000);
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
	while (!is_simulation_end(philo->table))
	{
		philo_think(philo);
		if (is_simulation_end(philo->table))
			break ;
		if (can_eat_more(philo))
			philo_eat(philo);
		else
			think_wait_death(philo);
		if (is_simulation_end(philo->table))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
