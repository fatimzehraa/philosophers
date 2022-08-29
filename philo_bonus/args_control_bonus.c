/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_control_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:45:14 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/29 16:20:12 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	test_args(int ac, char **av)
{
	if (!(ac == 4 || ac == 5))
	{
		return (0);
	}
	if (! is_all_number(av))
		return (0);
	return (1);
}

void	get_args(t_ctx *ctx, int ac, char **av)
{
	ctx->forks = ft_atoi(av[1]);
	ctx->time_to_die = ft_atoi(av[2]);
	ctx->time_to_eat = ft_atoi(av[3]);
	ctx->time_to_sleep = ft_atoi(av[4]);
	ctx->stop = 0;
	if (ac == 5)
		ctx->meals_nb = -1;
	else if (ac == 6)
		ctx->meals_nb = ft_atoi(av[5]);
}
