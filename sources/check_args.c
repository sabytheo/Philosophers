/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:49:48 by tsaby             #+#    #+#             */
/*   Updated: 2025/04/07 14:34:33 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				printf("Error:\narguments must be digit");
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
