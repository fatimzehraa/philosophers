/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:17:43 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/16 22:44:52 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

int main (int ac, char *av[])
{
	t_ctx		ctx;
//	t_philo		*philosophers;

	if(test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	//philosophers = 
	create_philosophers(&ctx);
	//if (check_dead_philo(philosophers))
	//	return (1);
	exit(0);
	return 0;
}
