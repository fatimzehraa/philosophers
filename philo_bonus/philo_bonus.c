/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:05:48 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 17:00:31 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>

int	is_alive(t_philo *philos)
{
	int		i;
	int		status;

	i = 0;
	while (i < philos->ctx->forks)
	{
		if (waitpid(philos[i].pid, &status, WNOHANG) != 0)
		{
			if (WIFEXITED(status) == 1)
				return (0);
		}
		i++;
	}
	return (1);
}

void	*parent_routine(void	*p)
{
	t_philo	*philos;
	int		i;

	philos = p;
	i = 0;
	while (i < philos->ctx->forks)
	{
		sem_wait(philos->ctx->all_meals);
		i++;
	}
	sem_wait(philos->ctx->printf_lock);
	stop_execution(philos, 0);
	return (NULL);
}

void	init_semaphore(t_ctx *ctx)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINTF_LOCK);
	ctx->printf_lock = sem_open(SEM_PRINTF_LOCK, O_CREAT, 0777, 1);
	ctx->all_forks = sem_open(SEM_FORKS, O_CREAT, 0777, ctx->forks);
	if (ctx->meals_nb != -1)
	{
		sem_unlink(SEM_MEALS_NB);
		ctx->all_meals = sem_open(SEM_MEALS_NB, O_CREAT, 0777, 0);
	}
}

void	creat_childs(t_philo *philos, t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->forks)
	{
		philos[i].pid = -1;
		i++;
	}
	i = 0;
	while (i < ctx->forks)
	{
		philos[i].ctx = ctx;
		philos[i].name = i + 1;
		philos[i].pid = (pid_t)fork();
		if (philos[i].pid < 0)
			stop_execution(philos, 1);
		else if (philos[i].pid == 0)
			do_child(philos + i);
		i++;
	}
}

void	create_philosophers(t_ctx *ctx)
{
	t_philo		*philos;
	pthread_t	parent_check;

	philos = malloc(ctx->forks * sizeof(t_philo));
	if (philos == NULL)
		return ;
	init_semaphore(ctx);
	ctx->start_time = ft_time();
	creat_childs(philos, ctx);
	if (ctx->meals_nb != -1
		&& pthread_create(&parent_check, NULL, &parent_routine, philos) != -1)
		pthread_detach(parent_check);
	while (is_alive(philos))
		;
	stop_execution(philos, 1);
}
