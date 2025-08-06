/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:56:52 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/06 19:34:21 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_table *table, pthread_t *monitor, pthread_t *threads)
{
    int i;

    if (pthread_create(monitor, NULL, monitor_philosophers, table) != 0)
        return (1);
    i = 0;
    while (i < table->philo_count)
    {
        if (pthread_create(&threads[i], NULL, philosopher_life, &table->philos[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

void join_threads(t_table *table, pthread_t monitor, pthread_t *threads)
{
    int i;

    pthread_join(monitor, NULL);
    i = 0;
    while (i < table->philo_count)
    {
        pthread_join(threads[i],NULL);
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_table *table;
    pthread_t monitor;
    pthread_t *threads;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    table = init_table(argc, argv);
    if (!table)
        return (1);
        
    init_philo(table);
    threads = malloc(sizeof(pthread_t) * table->philo_count);
    
    if(!threads || !create_threads(table, &monitor, threads))
        return (1);
    join_threads(table, monitor, threads);
    free(threads);
    cleanup_table(table);
    return (0);
}
