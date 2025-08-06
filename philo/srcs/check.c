/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:49:58 by skomatsu          #+#    #+#             */
/*   Updated: 2025/07/30 16:27:40 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_contains_non_digits(char **av)
{
    int i;

    i = 0;
    while ((**av >= 9 && **av <= 13) || **av == 32)
        (*av)++;
    if((*av)[i] == '+')
        i++;
    if((*av)[i] == '-')
        return (1);
    while ((*av)[i] >= '0' && (*av)[i] <= '9')
        i++;
    while ((**av >= 9 && **av <= 13) || **av == 32)
        i++;
    if ((*av)[i])
        return (1);
    return (0);
}

int check_arg(int ac, char **av)
{
    int i;
    int num;

    if (ac != 5 && ac != 6)
        return (error_msg("Usage", NULL, "./philo <number_of_philosophers> <time_to_die> \
        <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]"));
    i = 1;
    while (i < ac && av[i])
    {
        if (is_contains_non_digits(&av[i]) == 1)
    }
}