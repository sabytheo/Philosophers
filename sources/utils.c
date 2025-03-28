/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:46:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/28 16:21:32 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	fake_sleep(long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}

int	check_deaths(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->check_death);
	if (philo->rules->is_alive == 0)
	{
		pthread_mutex_unlock(&philo->rules->check_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->check_death);
	return (0);
}

int	check_isfull(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->check_isfull);
	if (philo->is_full == 1)
	{
		pthread_mutex_unlock(&philo->rules->check_isfull);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->check_isfull);
	return (0);
}

int	check_ifallfull(t_philo *philo)
{
	int	i;
	int size;

	i = 0;
	size = philo->rules->count_philos;
	while (i < size)
	{
		if (philo[i].is_full == 0)
			return (0);
		i++;
	}
	return (1);
}
