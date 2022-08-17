/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/17 17:37:12 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main (int ac, char *av[])
{
	t_ctx		ctx;
	t_philo		*philosophers;

	if(test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	philosophers = create_philosophers(&ctx);
	if (check_dead_philo(philosophers))
		return (1);
	exit(0);
	return 0;
}
