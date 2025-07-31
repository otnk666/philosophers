/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:56:52 by skomatsu          #+#    #+#             */
/*   Updated: 2025/07/31 18:45:36 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philo
{
    int id;
    int eat_count;
    long last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long start_time;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int *simulation_end;
    int must_eat_count;
} t_philo;

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *philosopher_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int i;
    printf("哲学者%d: スレッド開始\n", philo->id);
    i = 0;
    
    usleep(10000);
    while(i < 3 && !*(philo->simulation_end))
    {
        printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
        usleep(100000);  // 0.1秒思考
        
        // フォークを取る
        if (philo->id % 2 == 1)
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);

            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);

            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        }
        
        // 食事中
        printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
        philo->last_meal_time = get_time();
        philo->eat_count++;
        usleep(philo->time_to_eat * 1000);  // 食事時間待機
        
        // フォークを戻す
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
        // 睡眠中
        printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
        usleep(philo->time_to_sleep * 1000);  // 睡眠時間待機

        i++;
    }
    return (NULL);
}

int main(int argc, char *argv[])
{
    // if (check_arg(ac,av))
    
    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }

    int philo_count = ft_atoi(argv[1]);
    int time_to_die = ft_atoi(argv[2]);
    int time_to_eat = ft_atoi(argv[3]);
    int time_to_sleep = ft_atoi(argv[4]);
    
    long start_time = get_time();
    printf("開始時刻: %ld ms\n", start_time);
    int must_eat_count = -1;
    if (argc == 6)
    {
        must_eat_count = ft_atoi(argv[5]);
        if (must_eat_count <= 0)
        {
            ft_fputs("Error: must_eat_count must be positive\n", STDERR_FILENO);
            return (1);
        }
    }
    t_philo philos[philo_count];
    pthread_mutex_t forks[philo_count];

    int i = 0;
    while (i < philo_count)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    
    int simulation_end = 0;
    
    i = 0;
    while(i < philo_count)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].last_meal_time = start_time;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % philo_count];
        philos[i].start_time = start_time;
        philos[i].time_to_eat = time_to_eat;
        philos[i].time_to_sleep = time_to_sleep;
        philos[i].time_to_die = time_to_die;
        philos[i].simulation_end = &simulation_end;
        i++;
    }

    pthread_t threads[philo_count];
    for (int i = 0; i < philo_count; i++)
    {
        pthread_create(&threads[i], NULL, philosopher_life, &philos[i]);
    }
    
    while (!simulation_end)
    {
        i = 0;
        while(i < philo_count)
        {
            long current_time = get_time();
            if (current_time - philos[i].last_meal_time > time_to_die)
            {
                printf("%ld %d died\n", current_time - start_time, philos[i].id);
                simulation_end = 1;
                break;
            }
            i++;
        }
        usleep(1000);
    }

    for (int i = 0; i < philo_count; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    for (i = 0; i < philo_count; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    return (0);
}