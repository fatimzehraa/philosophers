/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 17:51:09 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char *av[])
{
	t_ctx		ctx;
	t_philo		*philosophers;
	int			dead;

	if (test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	philosophers = create_philosophers(&ctx);
	dead = check_dead_philo(philosophers);
	destroy_philos(philosophers);
	return (dead);
}
