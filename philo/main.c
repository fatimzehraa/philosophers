/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/12 22:43:48 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

int	check_dead_philo(t_philo *philosophers)
{
	long	start;
	int		time_to_die;
	int		has_eaten;
	int		i;

	start = philosophers->ctx->start_time;
	time_to_die = philosophers->ctx->time_to_die;
	while (1)
	{
		usleep(500);
		has_eaten = 1;
		i = 0;
		while (i < philosophers->ctx->forks)
		{
			if (philosophers[i].last_meal + time_to_die <= ft_diff_time(start))
			{
				printf("%ld %d is dead\n", ft_diff_time(start), philosophers[i].name);
				return 1;
			}
			if (philosophers[i].meals < philosophers->ctx->number_of_eating_times)
				has_eaten = 0;
			i++;
		}
		if (philosophers->ctx->number_of_eating_times != -1 && has_eaten)
			return (1);
	}
	return (1);
}

int main (int ac, char *av[])
{
	t_ctx		ctx;
	t_philo		*philosophers;

	if(test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	philosophers = NULL;
	philosophers = create_philosophers(&ctx, philosophers);
	if (check_dead_philo(philosophers))
		return (1);
//	run_philosophers();
//	printf("%d\n",ft_atoi("1234"));
	return 0;
}
