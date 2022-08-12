/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/12 22:54:51 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

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

void	ft_usleep(long time)
{
	unsigned int	first_sleep;
	unsigned int	time_left;
	long			starting_time;

	starting_time = ft_time();
	first_sleep = time * 0.95;
	time_left = time - first_sleep;
	usleep(first_sleep * 1000);
	while (time_left)
	{
		if (ft_time() - starting_time >= time)
			break ;
	}
}

void	*routine(void *p)
{
	t_philo *philosopher;
	long	start;
	int		name;

	philosopher = p;
	name = philosopher->name;
	start = philosopher->ctx->start_time;
	philosopher->last_meal = 0;
	//thinking
//	if (philosopher->ctx->forks % 2 == 1 && philosopher->name % 2 == 1)
//		ft_usleep(1);
	while (1)
	{
		printf("%ld %d is thinking\n", ft_diff_time(start),name);
		//wait for his left and right forks to be available
		if (name % 2 == 0)
		{
			pthread_mutex_lock(&philosopher->right_fork);
			printf("%ld %d has taken a fork\n", ft_diff_time(start), name);
			pthread_mutex_lock(philosopher->left_fork);
			printf("%ld %d has taken a fork\n", ft_diff_time(start), name);
		}
		else
		{
			pthread_mutex_lock(philosopher->left_fork);
			printf("%ld %d has taken a fork\n", ft_diff_time(start), name);
			pthread_mutex_lock(&philosopher->right_fork);
			printf("%ld %d has taken a fork\n", ft_diff_time(start), name);
		}
		//eating
		philosopher->last_meal = ft_diff_time(start);
		philosopher->meals++;
		printf("%ld %d is eating\n", philosopher->last_meal, name);
		ft_usleep(philosopher->ctx->time_to_eat);
		pthread_mutex_unlock(&philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		//sleeping
		printf("%ld %d is sleeping\n", ft_diff_time(start), name);
		ft_usleep(philosopher->ctx->time_to_sleep);
	}
	return (NULL);
}

t_philo	*create_philosophers(t_ctx *ctx, t_philo *philosophers)
{
	int i;

	philosophers = malloc(ctx->forks * sizeof(t_philo));
	if (philosophers == NULL)
		return (NULL);
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
	return (philosophers);
}
