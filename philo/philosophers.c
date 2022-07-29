/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/29 20:09:15 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

long	ft_time()
{
	long	time;
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	ft_diff_time(long start_time)
{
	long		timestamp_in_ms;

	timestamp_in_ms = ft_time() - start_time;
	return (timestamp_in_ms);
}

void	*routine(void *p)
{
	t_philo *philosopher;
	long	start;
	int		name;

	philosopher = p;
	name = philosopher->name;
	start = philosopher->ctx->start_time;
	//thinking
	while (1)
	{
		printf("%ld philosopher%d is thinking\n", ft_diff_time(start),name);
		pthread_mutex_lock(&philosopher->right_fork);
		printf("%ld philosopher%d has taken a fork\n", ft_diff_time(start), name);
		pthread_mutex_lock(philosopher->left_fork);
		printf("%ld philosopher%d has taken a fork\n", ft_diff_time(start),name);
		//wait for his left and right forks to be available
		//eating
		printf("%ld philosopher%d is eating\n", ft_diff_time(start), name);
		usleep(philosopher->ctx->time_to_eat * 1000);
		pthread_mutex_unlock(&philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		//sleeping
		usleep(philosopher->ctx->time_to_sleep * 1000);
		printf("%ld philosopher%d is sleeping\n", ft_diff_time(start), name);
	}
	return (NULL);
}

void	create_philosophers(t_ctx *ctx, t_philo *philosophers)
{
	int i;

	philosophers = malloc(ctx->forks * sizeof(t_philo));
//	printf("%d\n", ctx->forks);

	ctx->start_time = ft_time();
	i = 0;
	while (i < ctx->forks)
	{
		philosophers[i].ctx = ctx;
		pthread_mutex_init(&philosophers[i].right_fork, NULL);
		if (i == 0)
			philosophers[i].left_fork = &philosophers[ctx->forks - 1].right_fork;
		else
			philosophers[i].left_fork = &philosophers[i - 1].right_fork;
		philosophers[i].name = i + 1;
		if (pthread_create(&philosophers[i].thread, NULL, &routine, &philosophers[i]) != 0)
			exit (1);
		i++;
	}
	i = 0;
	while (i < ctx->forks)
	{
		philosophers[i].name = i + 1;
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}
