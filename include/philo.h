/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:03:40 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/21 20:02:46 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_rules
{
	int				count_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_alive;
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	writing;
	pthread_mutex_t	check_death;
	long			start_time;
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				count_meal;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}					t_philo;

/* utils*/

long				get_current_time(void);
void				fake_sleep(long time);
void				cancel_sim(t_rules *rules, t_philo *philos);

int					thread(t_philo *philos);

void				eat(t_philo *philo);

#endif
