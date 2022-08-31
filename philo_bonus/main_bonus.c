/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:17:43 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 17:04:52 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

int	main(int ac, char *av[])
{
	t_ctx	ctx;

	if (test_args(ac - 1, av + 1) == 0)
		return (-1);
	get_args(&ctx, ac, av);
	create_philosophers(&ctx);
	return (0);
}
