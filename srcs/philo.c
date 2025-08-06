/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:07:52 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/05 23:10:12 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_think(t_philo *philo)
{
    mutex_print(philo->table, philo->id, THINKING);
    usleep(1000);
}

void philo_sleep(t_philo *philo)
{
    mutex_print(philo->table, philo->id, SLEEPING);
    usleep(philo->table->time_to_sleep * 1000);
}

int check_continue(t_philo *philo)
{
    return (!is_simulation_end(philo->table) &&
            (philo->table->must_eat_count == -1 ||
             philo->eat_count < philo->table->must_eat_count));
}

void *philosopher_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    if (philo->id % 2 == 0)
        usleep(500);    
    while(check_continue(philo))
    {
        philo_think(philo);
        if(!check_continue(philo))
            break;   
        philo_eat(philo);
        if(!check_continue(philo))
            break;
        philo_sleep(philo);
    }
    return (NULL);
}