/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:45:26 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/07 20:16:06 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long time)
{
    long    start;
    long    target;
    long    current;
    long    elapsed;
    
    if (time <= 0)
        return;

    start = get_time();
    target = time;
    if (time > 5000)
        usleep((time - 2000));
        
    while (1)
    {
        current = get_time();
        elapsed = (current - start) * 1000;
        if (elapsed >= target)
            break;
        usleep(100);
    }
}