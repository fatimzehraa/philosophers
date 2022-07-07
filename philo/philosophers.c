/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:19:06 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/07 18:10:24 by ismail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
int ok = 1;
void	*routine()
{
	ok++;
	printf("%d\n", ok);
	return (NULL);
}

void	create_philosophers(t_ctx *ctx, t_philo *philosopher)
{
	int i;

	philosopher = malloc(ctx->forks * sizeof(t_philo));
	i = 0;
	printf("%d\n", ctx->forks);
	while (i < ctx->forks)
	{
		philosopher[i].name = i + 1;
		if (pthread_create(&philosopher[i].thread, NULL, &routine, NULL) != 0)
			exit (1);
		i++;
	}
}

pthread_t tread;
