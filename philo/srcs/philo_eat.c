/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:09:43 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/08 22:41:18 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int most_hunger_id(t_table *table)
{
    int hungeriest = 1;
    long oldest_meal;
    int i;
    
    pthread_mutex_lock(&table->death_mutex);
    oldest_meal = table->philos[0].last_meal_time;
    hungeriest = table->philos[0].id;
    i = 0;
    while (i < table->philo_count)
    {
        if (table->philos[i].last_meal_time < oldest_meal)
        {
            oldest_meal = table->philos[i].last_meal_time;
            hungeriest = table->philos[i].id;
        }
        i++;
    }
    pthread_mutex_unlock(&table->death_mutex);
    return (hungeriest);
}

int get_fork_algo(t_philo *philo)
{
    if (is_simulation_end(philo->table))
        return (0);

    t_fork *f1;
    t_fork *f2;

    if (philo->id % 2 == 0)
    {
        f1 = philo->left_fork;
        f2 = philo->right_fork;
    }
    else
    {
        f1 = philo->right_fork;
        f2 = philo->left_fork;
    }
    while(!is_simulation_end(philo->table))
    {    
        // if (most_hunger_id(philo->table) != philo->id)
        // {
        //     usleep(200);
        //     continue;
        // }
        pthread_mutex_lock(&f1->mutex);
        pthread_mutex_lock(&f2->mutex);
    
        if (f1->available && f2->available)
        {
            f1->available = 0;
            f2->available = 0;
            f1->last_used = philo->id;
            f2->last_used = philo->id;
            mutex_print(philo->table, philo->id, TAKE_FORKS);
            mutex_print(philo->table, philo->id, TAKE_FORKS);
            pthread_mutex_unlock(&f2->mutex);
            pthread_mutex_unlock(&f1->mutex);
            return (1);
        }
        pthread_mutex_unlock(&f2->mutex);
        pthread_mutex_unlock(&f1->mutex);
        usleep(200);
    }
    return (0);
}


void release_forks(t_philo *philo)
{
    t_fork *f1;
    t_fork *f2;

    if (philo->id % 2 == 0)
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
    f1->available = 1;
    f1->last_used = -1;
    pthread_mutex_unlock(&f1->mutex);

    pthread_mutex_lock(&f2->mutex);
    f2->available = 1;
    f2->last_used = -1;
    pthread_mutex_unlock(&f2->mutex);
}


void philo_eat(t_philo *philo)
{
    usleep(philo->id *2);
    if (!get_fork_algo(philo))
        return;
    pthread_mutex_lock(&philo->table->death_mutex);
    philo->last_meal_time = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->table->death_mutex);
    mutex_print(philo->table, philo->id, EATING);
    ft_usleep(philo->table->time_to_eat * 1000);
    release_forks(philo);
}