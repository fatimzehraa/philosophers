/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:05:48 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/29 22:36:08 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

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
			philo->ctx->stop = 1;
			printf("\033[1;33m");
			printf("%ld %d is dead\n", ft_diff_time(start), philo->name);
			printf("\033[0m");
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
	pthread_create(&philo->check, NULL, &routine, philo);
	pthread_detach(philo->check);
	while (1)
	{
		if (check_dead_philo(philo))
			exit(3);
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		sem_wait(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d has taken a fork\n", -1);
		philo->last_meal = ft_diff_time(start);
		ft_printf(philo->last_meal, philo,"%ld %d is eating\n", philo->ctx->time_to_eat);
		philo->meals++;
		//if (philo->meals == philo->ctx->meals_nb)
		//	sem_post(philo->ctx->all_meals);
		sem_post(philo->ctx->all_forks);
		sem_post(philo->ctx->all_forks);
		ft_printf(ft_diff_time(start), philo,"%ld %d is sleeping\n", philo->ctx->time_to_sleep);
		ft_printf(ft_diff_time(start), philo,"%ld %d is thinking\n", -1);
	}
}

void	kill_all_childs(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->ctx->forks)
	{
		kill(philos[i].pid, SIGQUIT);
		i++;
	}
}

void	stop_execution(t_philo *philos)
{
	philos->ctx->stop = 1;
	kill_all_childs(philos);
	free(philos);
	sem_close(philos->ctx->all_forks);
	sem_close(philos->ctx->printf_lock);
	//sem_close(philos->ctx->all_meals);
	exit(1);
}

int	is_alive(t_philo *philos)
{
	int i;
	int		status;

	i = 0;
	while (i < philos->ctx->forks)
	{
		if (waitpid(philos[i].pid, &status, WNOHANG) == -1)
			return (0);
		if (WIFEXITED(status) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	create_philosophers(t_ctx *ctx)
{
	t_philo	*philos;
	int		i;

	philos = malloc(ctx->forks * sizeof(t_philo));
	if (philos == NULL)
		return;
	sem_unlink("philo_forks");
	sem_unlink("print_lock");
	sem_unlink("if_they_eated_all");
	ctx->printf_lock = sem_open("print_lock", O_CREAT, 0777, 1);
	ctx->all_forks = sem_open("philo_forks", O_CREAT, 0777, ctx->forks);
	ctx->all_meals = sem_open("if_they_eated_all", O_CREAT, 0777, ctx->meals_nb);
	i = 0;
	ctx->start_time = ft_time();
	while (i < ctx->forks)
	{
		philos[i].ctx = ctx;
		philos[i].name = i + 1;
		philos[i].pid = (pid_t)fork();
		if (philos[i].pid < 0)
		{
			printf("hhhhhhhhhh\n");
			exit(1);
		}
		else if (philos[i].pid == 0)
			do_child(philos + i);
		i++;
	}
	/*
	while (i < ctx->forks)
	{
		sem_wait(ctx->all_meals);
		i++;
	}*/
	while (is_alive(philos));
	printf("rrrrr\n");
	stop_execution(philos);
}
