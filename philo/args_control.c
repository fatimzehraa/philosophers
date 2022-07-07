/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:45:14 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/05 13:45:49 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	test_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
	{
		return (0);
	}
	if (! is_all_number(av))
		return (0);
	//if (ac == 5) {
	//	
	//}
	return (1);
}

void	get_args(t_ctx *ctx, int ac, char **av)
{
	ctx->forks = ft_atoi(av[1]);
	ctx->time_to_die = ft_atoi(av[2]);
	ctx->time_to_eat = ft_atoi(av[3]);
	ctx->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		ctx->number_of_eating_times = -1;
	else if (ac == 6)
		ctx->number_of_eating_times = ft_atoi(av[5]);
}
