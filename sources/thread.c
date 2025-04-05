/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:50:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/05 23:00:03 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philos, char *action)
{
	if (check_deaths(philos) || check_isfull(philos))
		return ;
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
		if (check_deaths(philo) || check_isfull(philo))
			break ;
		eat(philo);
		if (check_deaths(philo))
			break ;
		print_action(philo, "is sleeping");
		fake_sleep(philo->rules->time_to_sleep);
		if (check_deaths(philo))
			break ;
		print_action(philo, "is thinking");
	}
	return (NULL);
}

static int	state_philo(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->rules->check_musteat);
	pthread_mutex_lock(&philo->rules->check_countmeal);
	if (philo[i].count_meal == philo->rules->must_eat)
	{
		pthread_mutex_lock(&philo->rules->check_isfull);
		philo[i].is_full = 1;
		pthread_mutex_unlock(&philo->rules->check_isfull);
	}
	pthread_mutex_unlock(&philo->rules->check_countmeal);
	pthread_mutex_unlock(&philo->rules->check_musteat);
	pthread_mutex_lock(&philo->rules->check_lastmeal);
	if (philo->rules->is_alive && get_current_time()
		- philo[i].last_meal > philo->rules->time_to_die)
	{
		print_action(&philo[i], "died");
		pthread_mutex_lock(&philo->rules->check_death);
		philo->rules->is_alive = 0;
		pthread_mutex_unlock(&philo->rules->check_death);
		pthread_mutex_unlock(&philo->rules->check_lastmeal);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->check_lastmeal);
	return (0);
}

int	monitor(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_deaths(philo) || check_ifallfull(philo))
			return (1);
		i = 0;
		while (i < philo->rules->count_philos)
		{
			if (state_philo(philo, i))
				return (1);
			i++;
		}
		usleep(100);
	}
	return (0);
}

int	thread(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->rules->count_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			return (1);
		i++;
	}
	if (monitor(philos))
	{
		return (1);
	}
	return (0);
}
