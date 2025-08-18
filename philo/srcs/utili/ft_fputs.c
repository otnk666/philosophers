/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:20:38 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/18 20:40:17 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fputs(char *s, int fd)
{
	int	l;
	int	ret;

	ret = 0;
	if (!s)
		ret = write(fd, "(null)", 6);
	else
	{
		l = 0;
		while (s[l])
			l++;
		ret = write(fd, s, l);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}
