/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:09:43 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/12 13:32:34 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int get_fork_algo(t_philo *philo)
{
    if (is_simulation_end(philo->table))
        return (0);

    t_fork *f1;
    t_fork *f2;

    if (philo->id % 2 == 1)
    {
        f1 = philo->left_fork;
        f2 = philo->right_fork;
    }
    else
    {
        f1 = philo->right_fork;
        f2 = philo->left_fork;
    }
    pthread_mutex_lock(&f1->mutex);
    mutex_print(philo->table, philo->id, TAKE_FORKS);
    pthread_mutex_lock(&f2->mutex);
    mutex_print(philo->table, philo->id, TAKE_FORKS);
        
    usleep(200);
    
    return (1);
}

void philo_eat(t_philo *philo)
{
    usleep(philo->id *2);
    if (!get_fork_algo(philo))
        return;
    pthread_mutex_lock(&philo->table->death_mutex);
    philo->last_meal_time = get_time();
    philo->eat_count++;
    mutex_print(philo->table, philo->id, EATING);
    pthread_mutex_unlock(&philo->table->death_mutex);
    ft_usleep(philo->table->time_to_eat * 1000);

    pthread_mutex_unlock(&philo->left_fork->mutex);
    pthread_mutex_unlock(&philo->right_fork->mutex);
    // release_forks(philo);
}