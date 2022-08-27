/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:36:15 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/27 22:52:25 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo philos)
{
	long	start;
	int		time_to_die;

	start = philos.ctx->start_time;
	time_to_die = philos.ctx->time_to_die;
	if (philos.last_meal + time_to_die <= ft_diff_time(start))
	{
		philos.ctx->stop = 1;
		pthread_mutex_lock(&philos.ctx->printf_lock);
		printf("\033[0;35m");
		printf("%ld %d died\n", ft_diff_time(start), philos.name);
		printf("\033[0m");
		return (1);
	}
	else
		return (0);
}

int	check_dead_philo(t_philo *philos)
{
	//long	start;
	//int		time_to_die;
	int		has_eaten;
	int		i;

	//start = philos->ctx->start_time;
	//time_to_die = philos->ctx->time_to_die;
	while (1)
	{
		usleep(100);
		has_eaten = 1;
		i = 0;
		while (i < philos->ctx->forks)
		{
			/*
			if (philos[i].last_meal + time_to_die <= ft_diff_time(start))
			{
				philos->ctx->stop = 1;
				pthread_mutex_lock(&philos->ctx->printf_lock);
				printf("\033[1;33m");
				printf("%ld %d is dead\n", ft_diff_time(start), philos[i].name);
				printf("\033[0m");
				return 1;
			}*/
			if (is_dead(philos[i]))
				return (1);
			if (philos[i].meals < philos->ctx->meals_nb)
				has_eaten = 0;
			i++;
		}
		if (philos->ctx->meals_nb != -1 && has_eaten)
			return (0) ;
	}
	return (1);
}

