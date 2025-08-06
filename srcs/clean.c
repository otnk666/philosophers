/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:56:28 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:37 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_mutex(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_count)
    {
        pthread_mutex_destroy(&table->print_mutex);
        i++;
    }
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->death_mutex);
}

void cleanup_table(t_table *table)
{
    if(!table)
        return;
    cleanup_mutex(table);
    free(table->forks);
    free(table->philos);
    free(table);
}