/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:14:48 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/07 22:13:38 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

#define TAKE_FORKS "has taken a fork"
#define THINKING "is thinking"
#define SLEEPING "is sleeping"
#define EATING "is eating"
#define DIED "died"

typedef struct s_table t_table;

typedef struct s_fork
{
    int id;
    pthread_mutex_t mutex;
    int available;
    int last_used;
} t_fork;

typedef struct s_philo
{
    int id;
    int eat_count;
    long last_meal_time;
    t_fork *left_fork;
    t_fork *right_fork;
    t_fork *first_fork;
    t_fork *second_fork;
    t_table *table;
} t_philo;

typedef struct s_table
{
    int philo_count;
    long start_time;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int simulation_end;
    int must_eat_count;
    
    t_fork *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    t_philo *philos;
} t_table;

int     ft_fputs(char *s, int fd);
int     ft_atoi(const char *str);
long    get_time(void);
void    ft_usleep(long time);
void    mutex_print(t_table *table, int id, char *action);
int     is_simulation_end(t_table *table);
void    set_simulation_end(t_table *table);
void    *monitor_philosophers(void *arg);
void    *philosopher_life(void *arg);
void    cleanup_table(t_table *table);
void    init_philo(t_table *table);
t_table *init_table(int argc, char **argv);
void    philo_eat(t_philo *philo);

#endif