/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 17:35:19 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void	*routine(void *p)
{
	t_philo	*philo;
	long	start;

	philo = p;
	start = philo->ctx->start_time;
	philo->last_meal = 0;
	if (philo->name % 2 == 1)
		usleep(100);
	while (1)
	{
		ft_printf(ft_diff_time(start), philo, "%ld %d is thinking\n", -1);
		pthread_mutex_lock(philo->left_fork);
		ft_printf(ft_diff_time(start), philo, "%ld %d has taken a fork\n", -1);
		pthread_mutex_lock(&philo->right_fork);
		ft_printf(ft_diff_time(start), philo, "%ld %d has taken a fork\n", -1);
		philo->last_meal = ft_diff_time(start);
		philo->meals++;
		ft_printf(philo->last_meal, philo,
			"%ld %d is eating\n", philo->ctx->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		ft_printf(ft_diff_time(start), philo,
			"%ld %d is sleeping\n", philo->ctx->time_to_sleep);
	}
	return (NULL);
}

t_philo	*create_forks(t_ctx *ctx)
{
	int		i;
	t_philo	*philos;

	philos = malloc(ctx->forks * sizeof(t_philo));
	if (philos == NULL)
		return (NULL);
	pthread_mutex_init(&ctx->printf_lock, NULL);
	i = 0;
	while (i < ctx->forks)
	{
		pthread_mutex_init(&philos[i].right_fork, NULL);
		if (i == 0)
			philos[i].left_fork = &philos[ctx->forks - 1].right_fork;
		else
			philos[i].left_fork = &philos[i - 1].right_fork;
		philos[i].ctx = ctx;
		philos[i].name = i + 1;
		i++;
	}
	return (philos);
}

void	*destroy_philos(t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&philos->ctx->printf_lock);
	i = 0;
	while (i < philos->ctx->forks)
	{
		pthread_mutex_destroy(&philos->right_fork);
		i++;
	}
	free(philos);
	return (NULL);
}

t_philo	*create_philosophers(t_ctx *ctx)
{
	int		i;
	t_philo	*philos;

	philos = create_forks(ctx);
	ctx->start_time = ft_time();
	i = 0;
	while (i < ctx->forks)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (NULL);
		pthread_detach(philos[i].thread);
		i++;
	}
	return (philos);
}
