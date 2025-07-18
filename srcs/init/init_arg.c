/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:22:16 by skomatsu          #+#    #+#             */
/*   Updated: 2025/07/12 14:03:16 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_arg(t_table *table, char **argv)
{
    int status;

    status = 0;
    table->philo_nbr = ft_atoi(argv[1]);

}