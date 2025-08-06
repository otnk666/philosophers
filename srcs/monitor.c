/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:08:50 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/05 23:07:50 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_all_finished(t_table *table)
{
    int i;

    if (table->must_eat_count <= 0)
        return (0);
    i = 0;
    while (i < table->philo_count)
    {
        if (table->philos[i].eat_count < table->must_eat_count)
            return (0);
        i++;
    }
    return (1);
}

int check_philo_death(t_table *table, int i)
{
    long current_time;

    current_time = get_time();
    if (current_time - table->philos[i].last_meal_time > table->time_to_die)
    {
        mutex_print(table, table->philos[i].id, DIED);
        set_simulation_end(table);
        return (1);
    }
    return (0);
}

void *monitor_philosophers(void *arg)
{
    t_table *table;
    int i;
    
    table = (t_table *)arg;
    while (!is_simulation_end(table))
    {
        if (check_all_finished(table))
        {
                set_simulation_end(table);
                break;
        }
        i = 0;
        while (i < table->philo_count)
        {
            if (check_philo_death(table, i))
                return (NULL);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}