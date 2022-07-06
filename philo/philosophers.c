/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/06 20:44:48 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
int ok = 1;
void	routine(void)
{
	ok++;
}

void	create_philosophers(t_ctx *ctx, t_philo *philosopher)
{
	int i;

	philosopher = malloc(ctx->forks * sizeof(t_philo));
	i = 0;
	while (i < ctx->forks)
	{
		philosopher[i].name = i + 1;
		pthread_create(&philosopher[i].thread, NULL, &routine, NULL);
		i++;
	}
}

pthread_t tread;
