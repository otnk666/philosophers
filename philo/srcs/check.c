/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:49:58 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/12 15:37:25 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_contains_non_digits(char *str)
{
    int i;

    if (!str)
        return (1);
    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

int check_arg(int ac, char **av)
{
    int i;

    if (ac != 5 && ac != 6)
    {
        return (error_msg("Usage", NULL, "./philo <number_of_philosophers> <time_to_die> \
        <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]"));
    }
    i = 1;
    while (i < ac)
    {
        if (is_contains_non_digits(av[i]))
        {
            return (error_msg("Error", NULL, "Arguments must be positive integers only"));
        }
        i++;
    }
    return (0);
}
