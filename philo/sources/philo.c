/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:01:47 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/08 15:44:32 by tsaby            ###   ########.fr       */
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

static int	set_value(t_rules *rules, int argc, char **argv)
{
	rules->is_alive = 1;
	rules->count_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	if (rules->count_philos <= 0 || rules->count_philos > MAX_PHILO
		|| rules->time_to_die <= 0 || rules->time_to_eat <= 0
		|| rules->time_to_sleep <= 0 || rules->must_eat == 0)
	{
		return (1);
	}
	return (0);
}

static int	init_rules(t_rules *rules, int argc, char **argv)
{
	int	i;

	i = 0;
	if (set_value(rules, argc, argv))
	{
		ft_putstr_fd("Error :\nset value issues", 2);
		return (1);
	}
	while (i < rules->count_philos)
	{
		rules->forks[i].is_taken = 0;
		pthread_mutex_init(&rules->forks[i].mutex, NULL);
		i++;
	}
	init_mutex(rules);
	rules->all_full = 0;
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
			philos[i].right_fork = &rules->forks[(i + 1) % rules->count_philos];
		}
		else
		{
			philos[i].right_fork = &rules->forks[(i + 1) % rules->count_philos];
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
		if (check_args(argc, argv) || check_value(argc, argv))
			return (1);
		ft_memset(&philos, 0, sizeof(philos));
		ft_memset(&rules, 0, sizeof(rules));
		if (init_rules(&rules, argc, argv))
			return (1);
		init_philos((t_philo *)philos, &rules);
		if (thread(philos))
		{
			i = 0;
			while (i < philos->rules->count_philos)
				if (pthread_join(philos[i++].thread, NULL))
					return (ft_putstr_fd("Failed to join threads", 2), 1);
		}
		return (0);
	}
	else
		return (ft_putstr_fd("Error :\ncheck the usage", 2), 1);
}
