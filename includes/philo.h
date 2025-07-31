/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:14:48 by skomatsu          #+#    #+#             */
/*   Updated: 2025/07/31 18:49:42 by skomatsu         ###   ########.fr       */
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

// typedef struct s_philo
// {
//     int id;
//     long last_eat_time;
//     int meals_eaten;
//     pthread_t thread;
//     pthread_mutex_t *r_fork;
//     pthread_mutex_t *l_fork;
//     t_table *table;
// }   t_philo;

// typedef struct s_monitor
// {
//     pthread_t   thread;
//     pthread_mutex_t mutex;
//     bool    is_stop;
// }   t_monitor;

// typedef struct s_table
// {
//     int     philo_nbr;
//     long    time_to_die;
//     long    time_to_eat;
//     long    time_to_sleep;
//     long    limit_meals;
//     long    start_time;
//     bool    is_set;

//     pthread_mutex_t *forks;
//     pthread_mutex_t print_mutex;
//     t_philo *philos;
//     t_monitor   monitor;
// } t_table;

int     ft_fputs(char *s, int fd);
int     ft_atoi(const char *str);

#endif