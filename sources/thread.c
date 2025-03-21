/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:50:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/21 20:03:59 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philos, char *action)
{
	pthread_mutex_lock(&philos->rules->writing);
	printf("%ld %d %s\n", (get_current_time() - philos->rules->start_time),
		philos->id, action);
	pthread_mutex_unlock(&philos->rules->writing);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->check_death);
        if (!philo->rules->is_alive)
        {
            pthread_mutex_unlock(&philo->rules->check_death);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->rules->check_death);
		eat(philo);
		print_action(philo, "is sleeping");
		fake_sleep(philo->rules->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;
	int		i;

	philo = (t_philo *)arg;
	rules = (*philo).rules;
	while (rules->is_alive)
	{
		i = 0;
		while (i < rules->count_philos)
		{
			pthread_mutex_lock(&rules->check_death);
			if (rules->is_alive && get_current_time()
				- philo[i].last_meal > rules->time_to_die)
			{
				print_action(&philo[i], "died");
				cancel_sim(rules, philo);
				pthread_mutex_unlock(&rules->check_death);
				pthread_exit(NULL);
			}
			pthread_mutex_unlock(&rules->check_death);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	eat(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	print_action(philos, "has taken a fork");
	pthread_mutex_lock(philos->right_fork);
	print_action(philos, "has taken a fork");
	print_action(philos, "is eating");
	philos->last_meal = get_current_time();
	philos->count_meal++;
	fake_sleep(philos->rules->time_to_eat);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

int	thread(t_philo *philos)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < philos->rules->count_philos)
	{
		pthread_create(&philos->thread, NULL, &routine, (void *)&philos[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor_thread, NULL, monitor, philos);
	pthread_join(monitor_thread, NULL);
	while (i < philos->rules->count_philos)
	{
		pthread_join(philos->thread, NULL);
		i++;
	}
	return (0);
}
