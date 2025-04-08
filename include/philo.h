/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:03:40 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/08 15:44:32 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_fork
{
	int				is_taken;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_rules
{
	int				count_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_alive;
	int				all_full;
	t_fork			forks[MAX_PHILO];
	pthread_mutex_t	writing;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_lastmeal;
	pthread_mutex_t	check_musteat;
	pthread_mutex_t	check_isfull;
	pthread_mutex_t	check_countmeal;
	long			start_time;
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				count_meal;
	long			last_meal;
	int				is_full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_rules			*rules;
}					t_philo;

long				get_current_time(void);
void				fake_sleep(long time, t_philo *philos);
int					check_value(int argc, char **argv);
int					check_args(int argc, char **argv);
int					check_deaths(t_philo *philo);
int					check_isfull(t_philo *philo);
int					check_ifallfull(t_philo *philo);

int					thread(t_philo *philos);

void				eat(t_philo *philo);
int					while_eating(t_philo *philos, t_fork *first_fork,
						t_fork *second_fork);
int					takes_forks(t_philo *philos, t_fork *first_fork,
						t_fork *second_fork);

void				print_action(t_philo *philos, char *action);

#endif
