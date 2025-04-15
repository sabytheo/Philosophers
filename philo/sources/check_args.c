/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:49:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/15 17:03:12 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_philo *philos)
{
	int	i;

	if (!philos)
		return ;
	if (philos->left_fork && philos->right_fork)
	{
		i = 0;
		while (i < philos->rules->count_philos)
		{
			pthread_mutex_destroy(&philos->rules->forks[i].mutex);
			i++;
		}
	}
	pthread_mutex_destroy(&philos->rules->writing);
	pthread_mutex_destroy(&philos->rules->check_countmeal);
	pthread_mutex_destroy(&philos->rules->check_death);
	pthread_mutex_destroy(&philos->rules->check_isfull);
	pthread_mutex_destroy(&philos->rules->check_lastmeal);
	pthread_mutex_destroy(&philos->rules->check_musteat);
}

static long	ft_atol(const char *str)
{
	size_t	i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error:\nargs must be digit");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_value(int argc, char **argv)
{
	long	value;
	int		i;

	i = 1;
	while (i < argc)
	{
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < 0)
		{
			printf("Error:\nthe value must be an int, and can't be negative");
			return (1);
		}
		i++;
	}
	return (0);
}

int	clean_error(char *error_message, t_philo *philo, int state)
{
	if (error_message)
		ft_putstr_fd(error_message, 2);
	if (state)
		destroy_mutex(philo);
	return (1);
}
