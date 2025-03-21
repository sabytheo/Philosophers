/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:46:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/21 16:37:22 by tsaby            ###   ########.fr       */
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

void	cancel_sim(t_rules *rules, t_philo *philos)
{
	int	i;

	pthread_mutex_lock(&rules->check_death);
	rules->is_alive = 0;
	pthread_mutex_unlock(&rules->check_death);
	i = 0;
	while (i < rules->count_philos)
	{
		pthread_join(philos[i].thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&rules->check_death);
	pthread_mutex_destroy(&rules->writing);
	// free(rules->forks);
	free(philos);
}
