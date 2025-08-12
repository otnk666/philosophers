/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:22:16 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/12 15:36:06 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(t_table *table)
{
    int64_t i;
    
    i = 0;
    while (i < table->philo_count)
    {
        table->forks[i].id = i;
        table->forks[i].available = 1;
        table->forks[i].last_used = -1;
        if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
        {
            ft_fputs("Error: fork mutex init failed\n", STDERR_FILENO);
            return;        
        }
        i++;
    }
}

void init_philo(t_table *table)
{
    int64_t i;
    
    i = 0;
    while (i < table->philo_count)
    {
        table->philos[i].id = i + 1;
        table->philos[i].eat_count = 0;
        table->philos[i].last_meal_time = table->start_time;
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_count];
        table->philos[i].table = table;
        i++;
    }
}

int init_table_values(t_table *table, int argc, char **argv)
{
    table->philo_count = ft_atoi64(argv[1]);
    table->time_to_die = ft_atoi64(argv[2]);
    table->time_to_eat = ft_atoi64(argv[3]);
    table->time_to_sleep = ft_atoi64(argv[4]);
    if (argc == 6)
        table->must_eat_count = ft_atoi64(argv[5]);
    else
        table->must_eat_count = -1;
    table->start_time = get_time();
    table->simulation_end = 0;
    return (0);
}

int init_table_memory(t_table *table)
{
    table->forks = malloc(sizeof(t_fork) * table->philo_count);
    if (!table->forks)
    {
        ft_fputs("Error: malloc failed for forks\n", STDERR_FILENO);
        free(table);
        return (1);
    }
    table->philos = malloc(sizeof(t_philo) * table->philo_count);
    if (!table->philos)
    {
        ft_fputs("Error: malloc failed for philos\n", STDERR_FILENO);
        free(table->forks);
        free(table);
        return (1);
    } 
    return (0);
}

int init_table_mutex(t_table *table)
{
    if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
        return (1);
    return (0);
}

t_table *init_table(int argc, char **argv)
{
    t_table *table;
    
    table = malloc(sizeof(t_table));
    if (!table)
        return (NULL);
    init_table_values(table, argc, argv);
    if (init_table_memory(table) != 0)
        return (NULL);
    if (init_table_mutex(table) != 0)
    {
        free(table->forks);
        free(table->philos);
        free(table);
        return (NULL);
    }
    init_forks(table);
    return (table);
}
