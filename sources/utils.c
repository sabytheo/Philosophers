/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:46:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/27 17:37:36 by tsaby            ###   ########.fr       */
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
