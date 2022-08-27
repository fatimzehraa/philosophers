/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:05:48 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/27 15:44:26 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#include <unistd.h>

void	do_child(t_philo *philo)
{
	long	start;

	start = philo->ctx->start_time;
	while (1)
	{
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		ft_printf(philo->last_meal, philo,"%ld %d is eating\n", philo->ctx->time_to_eat);
		philo->last_meal = ft_diff_time(start);
		philo->meals++;
		sem_post(philo->ctx->all_forks);
		sem_post(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d is sleeping\n", philo->ctx->time_to_sleep);
		ft_printf(ft_diff_time(start), philo,"%ld %d is thinking\n", -1);
		if (check_dead_philo(philo))
			exit(3);
	}
}

t_philo	*create_philosophers(t_ctx *ctx)
{
	t_philo	*philos;
	int		i;
	int		status;

	philos = malloc(ctx->forks * sizeof(t_philo));
	if (philos == NULL)
		return (NULL);
	sem_unlink("philo_forks");
	ctx->all_forks = sem_open("philo_forks", O_CREAT, 0777, ctx->forks);
	i = 0;
	ctx->start_time = ft_time();
	while (i < ctx->forks)
	{
		philos[i].ctx = ctx;
		philos[i].name = i + 1;
		philos[i].pid = (pid_t)fork();
		if (philos[i].pid < 0)
			exit(1);
		else if (philos[i].pid == 0)
			do_child(philos + i);
		i++;
	}
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (WIFEXITED(status) == 1)
			break ;
	}
	sem_close(philos->ctx->all_forks);
	return (philos);
}
