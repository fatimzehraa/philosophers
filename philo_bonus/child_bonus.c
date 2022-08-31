/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:42:17 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 18:16:05 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

void	*routine(void *p)
{
	t_philo	*philo;
	long	start;
	int		time_to_die;

	philo = p;
	start = philo->ctx->start_time;
	time_to_die = philo->ctx->time_to_die;
	while (1)
	{
		if (philo->last_meal + time_to_die <= ft_diff_time(start))
		{
			sem_wait(philo->ctx->printf_lock);
			philo->ctx->stop = 1;
			printf("%ld %d died\n", ft_diff_time(start), philo->name);
			exit (3);
		}
	}
	return (philo);
}

void	do_child(t_philo *philo)
{
	long	start;

	start = philo->ctx->start_time;
	philo->last_meal = 0;
	philo->meals = 0;
	pthread_create(&philo->check, NULL, &routine, philo);
	pthread_detach(philo->check);
	while (1)
	{
		ft_printf(ft_diff_time(start), philo, "%ld %d is thinking\n", -1);
		ft_printf(ft_diff_time(start), philo, "%ld %d is thinking\n", 0);
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo, "%ld %d has taken a fork\n", -1);
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo, "%ld %d has taken a fork\n", -1);
		philo->last_meal = ft_diff_time(start);
		ft_printf(philo->last_meal, philo,
			"%ld %d is eating\n", philo->ctx->time_to_eat);
		philo->meals++;
		if (philo->meals == philo->ctx->meals_nb)
			sem_post(philo->ctx->all_meals);
		sem_post(philo->ctx->all_forks);
		sem_post(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,
			"%ld %d is sleeping\n", philo->ctx->time_to_sleep);
	}
}
