/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skomatsu <skomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:14:48 by skomatsu          #+#    #+#             */
/*   Updated: 2025/08/29 19:51:48 by skomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORKS "has taken a fork"
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_table	t_table;

typedef struct s_fork
{
	int64_t				id;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_philo
{
	int64_t				id;
	int					eat_count;
	int64_t				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_fork				*first;
	t_fork				*second;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int64_t				philo_count;
	int64_t				start_time;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int64_t				time_to_die;
	int					simulation_end;
	int					must_eat_count;
	t_fork				*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	t_philo				*philos;
}						t_table;

int						check_arg(int ac, char **av);
int						error_msg(char *msg_type, char *error, char *msg);
int						ft_fputs(char *s, int fd);
int						ft_strlen(char *str);
int						ft_strcmp(char *s1, char *s2);
int64_t					ft_atoi64(const char *str);
t_table					*init_table(int argc, char **argv);
void					init_forks(t_table *table);
void					init_philo(t_table *table);
long					get_time(void);
void					ft_usleep(long time);
void					mutex_print(t_table *table, int id, char *action);
int						is_simulation_end(t_table *table);
int						set_simulation_end(t_table *table);
void					*monitor_philosophers(void *arg);
void					*philosopher_life(void *arg);
void					cleanup_table(t_table *table);
void					philo_eat(t_philo *philo);

#endif