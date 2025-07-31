/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utili.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:01:00 by skomatsu          #+#    #+#             */
/*   Updated: 2025/07/25 05:14:32 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_fputs(char *s, int fd)
{
    int l;
    int ret;

    ret = 0;
    if(!s)
        ret = write(fd,"(null)", 6);
    else
    {
        l = 0;
        while(s[l])
            l++;
        ret = write(fd, s, l);
    }
    if (ret < 0)
        return (-1);
    return(ret);
}

