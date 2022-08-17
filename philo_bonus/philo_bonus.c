/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:05:48 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/17 18:28:40 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <unistd.h>

void	do_child(t_philo *philo)
{
	while (1)
	{
		
	if (sem_wait(philo->forks) == 0)
	{
		printf("philospher %d has taken a fork\n", philo->name);
		if (sem_wait(philo->forks) == 0)
		{
			printf("philospher %d has taken a fork\n", philo->name);
			printf("philospher %d is eating\n", philo->name);
			ft_usleep(philo->ctx->time_to_eat);
		}
	}
	sem_post(philo->forks);
	sem_post(philo->forks);
	printf("philospher %d is sleeping\n", philo->name);
	ft_usleep(philo->ctx->time_to_sleep);
	printf("philospher %d is thinking\n", philo->name);
	if (check_dead_philo(philo))
		exit(1);
	}
}

t_philo	*create_philosophers(t_ctx *ctx)
{
	t_philo	*philos;
	int		i;

	philos = malloc(ctx->forks * sizeof(t_philo));
	if (philos == NULL)
		return (NULL);
	sem_unlink("philo_forks");
	philos->forks = sem_open("philo_forks", O_CREAT, 0777, ctx->forks);
	i = 0;
	while (i < ctx->forks)
	{
		philos->pids[i] = fork();
		if (philos->pids[i] < 0)
			exit(1);
		else if (philos->pids[i] == 0)
			do_child(philos);
		i++;
	}
	sem_close(philos->forks);
	return (philos);
}
