/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:01:47 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/31 16:00:04 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_rules *rules)
{
	pthread_mutex_init(&rules->writing, NULL);
	pthread_mutex_init(&rules->check_death, NULL);
	pthread_mutex_init(&rules->check_lastmeal, NULL);
	pthread_mutex_init(&rules->check_musteat, NULL);
	pthread_mutex_init(&rules->check_isfull, NULL);
	pthread_mutex_init(&rules->check_countmeal, NULL);
}

static int	init_rules(t_rules *rules, int argc, char **argv)
{
	int	i;

	i = 0;
	rules->is_alive = 1;
	rules->count_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	if (rules->count_philos <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
		exit(EXIT_FAILURE);
	while (i < rules->count_philos)
	{
		rules->forks[i].is_taken = 0;
		pthread_mutex_init(&rules->forks[i].mutex, NULL);
		i++;
	}
	init_mutex(rules);
	rules->start_time = get_current_time();
	return (0);
}

static void	init_philos(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->count_philos)
	{
		philos[i].id = i + 1;
		philos[i].count_meal = 0;
		philos[i].last_meal = get_current_time();
		philos[i].is_full = 0;
		philos[i].rules = rules;
		if (i % 2 == 0)
		{
			philos[i].left_fork = &rules->forks[i];
			philos[i].right_fork = &rules->forks[(i + 1 % rules->count_philos)];
		}
		else
		{
			philos[i].right_fork = &rules->forks[(i + 1 % rules->count_philos)];
			philos[i].left_fork = &rules->forks[i];
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILO];
	t_rules	rules;
	int		i;

	if (argc == 5 || argc == 6)
	{
		i = 0;
		ft_memset(&philos, 0, sizeof(t_philo));
		ft_memset(&rules, 0, sizeof(t_rules));
		init_rules(&rules, argc, argv);
		init_philos((t_philo *)philos, &rules);
		if (thread(philos))
		{
			while (i < philos->rules->count_philos)
			{
				if (pthread_join(philos[i].thread, NULL))
					return (1);
				i++;
			}
		}
		return (0);
	}
	else
		return (1);
}
