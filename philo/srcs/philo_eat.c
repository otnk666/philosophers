/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:09:43 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/07 22:36:45 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_fork_algo(t_philo *philo)
{
    if (is_simulation_end(philo->table))
        return (0);
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(&philo->first_fork->mutex);
        if (is_simulation_end(philo->table))
        {
            pthread_mutex_unlock(&philo->first_fork->mutex);
            return (0);
        }
        philo->first_fork->available = 0;
        philo->first_fork->last_used = philo->id;
        mutex_print(philo->table, philo->id, TAKE_FORKS);
        pthread_mutex_lock(&philo->second_fork->mutex);
        if (is_simulation_end(philo->table))
        {
            philo->first_fork->available = 1;
            philo->first_fork->last_used = -1;
            pthread_mutex_unlock(&philo->first_fork->mutex);
            pthread_mutex_unlock(&philo->second_fork->mutex);
            return (0);
        }
        philo->second_fork->available = 0;
        philo->second_fork->last_used = philo->id;
        mutex_print(philo->table, philo->id, TAKE_FORKS);
    }
    return (1);
}

// static void get_fork_order(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second)
// {
//     // 基本的にはフォークのアドレスで順序を決定
//     if (philo->left_fork < philo->right_fork)
//     {
//         *first = philo->left_fork;
//         *second = philo->right_fork;
//     }
//     else
//     {
//         *first = philo->right_fork;
//         *second = philo->left_fork;
//     }
    
//     // 奇数番目の哲学者は順序を逆にする（より確実なデッドロック回避）
//     if (philo->id % 2 == 1)
//     {
//         pthread_mutex_t *temp = *first;
//         *first = *second;
//         *second = temp;
//     }
// }

// int get_fork_algo(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;
    
//     if (is_simulation_end(philo->table))
//         return (0);
    
//     get_fork_order(philo, &first_fork, &second_fork);
    
//     // 第1フォーク取得
//     pthread_mutex_lock(first_fork);
//     if (is_simulation_end(philo->table))
//     {
//         pthread_mutex_unlock(first_fork);
//         return (0);
//     }
//     mutex_print(philo->table, philo->id, TAKE_FORKS);
    
//     // タイトなタイミングでは短い遅延を追加
//     if (philo->table->time_to_die <= 500)
//         usleep(100);
    
//     // 第2フォーク取得
//     pthread_mutex_lock(second_fork);
//     if (is_simulation_end(philo->table))
//     {
//         pthread_mutex_unlock(second_fork);
//         pthread_mutex_unlock(first_fork);
//         return (0);
//     }
//     mutex_print(philo->table, philo->id, TAKE_FORKS);
    
//     return (1);
// }


void release_forks(t_philo *philo)
{
    philo->second_fork->available =1;
    philo->second_fork->last_used = -1;
    pthread_mutex_unlock(&philo->second_fork->mutex);
    philo->first_fork->available = 1;
    philo->first_fork->last_used = -1;
    pthread_mutex_unlock(&philo->first_fork->mutex);
}

// void release_forks(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;
    
//     get_fork_order(philo, &first_fork, &second_fork);
    
//     // 取得と逆順で解放
//     pthread_mutex_unlock(second_fork);
//     pthread_mutex_unlock(first_fork);
// }


void philo_eat(t_philo *philo)
{
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