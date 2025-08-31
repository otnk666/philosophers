/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:16:24 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/31 15:13:13 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg_type, char *error, char *msg)
{
	ft_fputs("philo:", STDERR_FILENO);
	if (msg_type)
		ft_fputs(msg_type, STDERR_FILENO);
	if (error)
	{
		ft_fputs(": '", STDERR_FILENO);
		ft_fputs(error, STDERR_FILENO);
		ft_fputs("'", STDERR_FILENO);
	}
	if (msg)
	{
		ft_fputs(": ", STDERR_FILENO);
		ft_fputs(msg, STDERR_FILENO);
	}
	ft_fputs("\n", STDERR_FILENO);
	return (1);
}

int	error_error(char *msg)
{
	ft_fputs("philo: Error", STDERR_FILENO);
	if (msg)
	{
		ft_fputs(": ", STDERR_FILENO);
		ft_fputs(msg, STDERR_FILENO);
	}
	ft_fputs("\n", STDERR_FILENO);
	return (1);
}

int	error_usage(char *msg)
{
	ft_fputs("philo: Usage", STDERR_FILENO);
	if (msg)
	{
		ft_fputs(": ", STDERR_FILENO);
		ft_fputs(msg, STDERR_FILENO);
	}
	ft_fputs("\n", STDERR_FILENO);
	return (1);
}
