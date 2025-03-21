/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:01:47 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/21 18:23:54 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (rules->count_philos <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
		exit(EXIT_FAILURE);
	while (i < rules->count_philos)
	{
		pthread_mutex_init(&rules->forks[i],NULL);
		i++;
	}
	pthread_mutex_init(&rules->writing, NULL);
	pthread_mutex_init(&rules->check_death, NULL);
	rules->start_time = get_current_time();
	return (0);
}

static void	init_philos(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->count_philos)
	{
		philos[i].id = i;
		philos[i].count_meal = 0;
		philos[i].last_meal = get_current_time();
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[i + 1];
		i++;
	}
}

void	destroy_mutex(t_rules *rules)
{
	int i ;

	i = 0;

	while (i < rules->count_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->writing);
}

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILO];
	t_rules	rules;

	ft_memset(&philos, 0, sizeof(t_philo));
	ft_memset(&rules, 0, sizeof(t_rules));
	init_rules(&rules, argc, argv);
	init_philos((t_philo *)philos, &rules);
	thread(philos);
	// printf("nombre de philo : %d\ntime_to_die : %d\ntime_to_eat : %d\ntime_to_sleep : %d\n start_time : %ld\n ", rules.count_philos,rules.time_to_die,rules.time_to_eat,rules.time_to_sleep,rules.start_time);
	destroy_mutex(&rules);
	return(0);
}
