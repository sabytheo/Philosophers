/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:46:45 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/21 00:12:53 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


void fake_sleep(long time)
{
	long start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}

void cancel_sim(t_rules *rules)
{
	pthread_mutex_lock(&rules->check_death);
	rules->is_alive = 0;
	pthread_mutex_unlock(&rules->check_death);
	exit(EXIT_FAILURE);
}
