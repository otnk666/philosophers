/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:45:26 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/11 23:52:56 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long time)
{
    long    start;
    long    current;
    long    elapsed;
    
    if (time <= 0)
        return;

    start = get_time();
    while (1)
    {
        current = get_time();
        elapsed = (current - start) * 1000;
        if (elapsed >= time)
            break;
        if (time - elapsed > 1000)
            usleep(500);
        else
            usleep(100);
    }
}