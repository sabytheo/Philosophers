/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:59:11 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/03 10:44:11 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takes_forks(t_philo *philos)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = philos->left_fork;
	second_fork = philos->right_fork;
	if (first_fork > second_fork)
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	pthread_mutex_lock(&second_fork->mutex);
	if (!philos->left_fork->is_taken && !philos->right_fork->is_taken
		&& !check_deaths(philos))
	{
		philos->left_fork->is_taken = 1;
		print_action(philos, "has taken a fork");
		philos->right_fork->is_taken = 1;
		print_action(philos, "has taken a fork");
		pthread_mutex_unlock(&first_fork->mutex);
		pthread_mutex_unlock(&second_fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
	return (0);
}

int	while_eating(t_philo *philos)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = philos->left_fork;
	second_fork = philos->right_fork;
	if (philos->left_fork > philos->right_fork)
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	pthread_mutex_lock(&second_fork->mutex);
	if (philos->left_fork->is_taken && philos->right_fork->is_taken)
	{
		print_action(philos, "is eating");
		pthread_mutex_lock(&philos->rules->check_lastmeal);
		philos->last_meal = get_current_time();
		pthread_mutex_unlock(&philos->rules->check_lastmeal);
		pthread_mutex_lock(&philos->rules->check_countmeal);
		philos->count_meal++;
		pthread_mutex_unlock(&philos->rules->check_countmeal);
		fake_sleep(philos->rules->time_to_eat);
		philos->left_fork->is_taken = 0;
		philos->right_fork->is_taken = 0;
	}
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
	return (1);
}


void	eat(t_philo *philos)
{
	while (1)
	{
		if (!check_deaths(philos))
			takes_forks(philos);
		break ;
	}
	if (!check_deaths(philos))
		while_eating(philos);
	return ;
}
