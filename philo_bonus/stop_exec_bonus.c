/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_exec_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:47:28 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 16:52:45 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <signal.h>

void	kill_all_childs(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->ctx->forks)
	{
		if (philos[i].pid > 0)
			kill(philos[i].pid, SIGQUIT);
		i++;
	}
}

void	stop_execution(t_philo *philos, int retval)
{
	t_ctx	*ctx;

	ctx = philos[0].ctx;
	ctx->stop = 1;
	kill_all_childs(philos);
	sem_close(ctx->all_forks);
	sem_close(ctx->printf_lock);
	if (ctx->meals_nb != -1)
	{
		sem_post(ctx->all_meals);
		sem_close(ctx->all_meals);
	}
	free(philos);
	exit(retval);
}
