/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/27 15:52:10 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/*void	routine_helper(t_philo *philosopher)
{
	int		name;
	long	start;
	
	name = philosopher->name;
	start = philosopher->ctx->start_time;
	if (name % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->right_fork);
		ft_printf(ft_diff_time(start), philosopher,"%ld %d has taken a fork\n");
		pthread_mutex_lock(philosopher->left_fork);
		ft_printf(ft_diff_time(start), philosopher,"%ld %d has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philosopher->left_fork);
		ft_printf(ft_diff_time(start), philosopher,"%ld %d has taken a fork\n");
		pthread_mutex_lock(&philosopher->right_fork);
		ft_printf(ft_diff_time(start), philosopher,"%ld %d has taken a fork\n");
	}
}*/

void	*routine(void *p)
{
	t_philo *philo;
	long	start;
	//int		name;

	philo = p;
	//name = philosopher->name;
	start = philo->ctx->start_time;
	philo->last_meal = 0;
	//thinking
/*	if (philosopher->ctx->forks % 2 == 1 && philosopher->name % 2 == 1)
	{
		printf("we gonna sleeeeeep\n");
		ft_usleep(5);
	}*/
	while (1)
	{
		//routine_helper(philosopher);
		if (philo->name % 2 == 1)
			pthread_mutex_lock(&philo->right_fork);
		else
			pthread_mutex_lock(philo->left_fork);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		if (philo->name % 2 == 1)
			pthread_mutex_lock(philo->left_fork);
		else
			pthread_mutex_lock(&philo->right_fork);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		//wait for his left and right forks to be available
		//eating
		philo->last_meal = ft_diff_time(start);
		philo->meals++;
		ft_printf(philo->last_meal, philo,"%ld %d is eating\n", philo->ctx->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		//sleeping
		ft_printf(ft_diff_time(start), philo,"%ld %d is sleeping\n", philo->ctx->time_to_sleep);
		ft_printf(ft_diff_time(start), philo,"%ld %d is thinking\n", -1);
	}
	return (NULL);
}

t_philo	*create_philosophers(t_ctx *ctx)
{
	int i;
	t_philo *philos;

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
	ctx->start_time = ft_time();
	i = 0;
	while (i < ctx->forks)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return NULL;
		i++;
	}
	return (philos);
}
