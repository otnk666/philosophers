/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:09:43 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/06 21:53:34 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_fork_algo(t_philo *philo)
{
    if (is_simulation_end(philo->table))
        return (0);
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        if (is_simulation_end(philo->table))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (0);
        }
        mutex_print(philo->table, philo->id, TAKE_FORKS);
        pthread_mutex_lock(philo->right_fork);
        if (is_simulation_end(philo->table))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (0);
        }
        mutex_print(philo->table, philo->id, TAKE_FORKS);
    }
    else
    {
        usleep(50);
        pthread_mutex_lock(philo->right_fork);
        if (is_simulation_end(philo->table))
        {
            pthread_mutex_unlock(philo->right_fork);
            return (0);
        }
        mutex_print(philo->table, philo->id, TAKE_FORKS);
        pthread_mutex_lock(philo->left_fork);
        if (is_simulation_end(philo->table))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);        
            return (0);
        }
        mutex_print(philo->table, philo->id, TAKE_FORKS);
    }
    return (1);
}

void release_forks(t_philo *philo)
{
    if (philo->id % 2 == 1)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void philo_eat(t_philo *philo)
{
    if (!get_fork_algo(philo))
        return;
    mutex_print(philo->table, philo->id, EATING);
    pthread_mutex_lock(&philo->table->death_mutex);
    philo->last_meal_time = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->table->death_mutex);
    usleep(philo->table->time_to_eat * 1000);
    release_forks(philo);
}