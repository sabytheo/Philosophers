/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:50:42 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/26 15:15:52 by tsaby            ###   ########.fr       */
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
	while (philo->rules->is_alive)
	{
        if (check_deaths(philo))
            break;
		else
			eat(philo);
		if (check_deaths(philo))
			break;
		else
		{
			print_action(philo, "is sleeping");
			fake_sleep(philo->rules->time_to_sleep);
		}
		if (check_deaths(philo))
			break;
		else
			print_action(philo, "is thinking");
	}
	return (NULL);
}

int	monitor(t_philo *philo)
{
	int		i;

	while (philo->rules->is_alive)
	{
		i = 0;
		while (i < philo->rules->count_philos)
		{
			pthread_mutex_lock(&philo->rules->check_lastmeal);
			if (philo->rules->is_alive && get_current_time()
			- philo[i].last_meal > philo->rules->time_to_die)
			{
				print_action(&philo[i], "died");
				pthread_mutex_lock(&philo->rules->check_death);
				philo->rules->is_alive = 0;
				pthread_mutex_unlock(&philo->rules->check_death);
				cancel_sim(philo->rules, philo);
				pthread_mutex_unlock(&philo->rules->check_death);
				pthread_mutex_unlock(&philo->rules->check_lastmeal);
				return(1);
			}
			pthread_mutex_unlock(&philo->rules->check_lastmeal);
			i++;
		}
		usleep(100);
	}
	return (0);
}

void	eat(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	print_action(philos, "has taken a fork");
	if (check_deaths(philos))
	{
		pthread_mutex_unlock(philos->left_fork);
		return ;
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		print_action(philos, "has taken a fork");
		print_action(philos, "is eating");
		pthread_mutex_lock(&philos->rules->check_lastmeal);
		philos->last_meal = get_current_time();
		pthread_mutex_unlock(&philos->rules->check_lastmeal);
		philos->count_meal++;
		fake_sleep(philos->rules->time_to_eat);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
}

int	thread(t_philo *philos)
{
	int			i;

	i = 0;
	while (i < philos->rules->count_philos)
	{
		pthread_create(&philos->thread, NULL, &routine, (void *)&philos[i]);
		i++;
	}
	if (monitor(philos))
		return (1);
	return (0);
}
