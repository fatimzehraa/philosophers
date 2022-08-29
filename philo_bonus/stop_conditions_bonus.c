/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_conditions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:36:15 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/29 21:45:31 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_dead_philo(t_philo *philo)
{
//	long	start;
//	int		time_to_die;
	int		has_eaten;

//	start = philo->ctx->start_time;
//	time_to_die = philo->ctx->time_to_die;
	has_eaten = 1;
	/*
	if (philo->last_meal + time_to_die <= ft_diff_time(start))
	{
		printf("\033[1;33m");
		printf("%ld %d is dead\n", ft_diff_time(start), philo->name);
		printf("\033[0m");
		return (1);
	}
	else
	{*/
		printf("df\n");
	if (philo->meals < philo->ctx->meals_nb)
		has_eaten = 0;
	else if (philo->ctx->meals_nb != -1 && has_eaten)
		return (1);
	//}
	return (0);
}

