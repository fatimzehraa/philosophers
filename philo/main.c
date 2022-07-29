/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/28 02:44:48 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>


int main (int ac, char *av[])
{
	t_ctx		ctx;
	t_philo		philosopher;

	if(test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	create_philosophers(&ctx, &philosopher);
//	run_philosophers();
//	printf("%d\n",ft_atoi("1234"));
	return 0;
}
