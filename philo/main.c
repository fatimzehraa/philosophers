/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:51:58 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/03 19:55:24 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

int	ft_atoi(char *str)
{
	int nb = 0;
	int i = 0;
	int k = 1;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb * 10 + str[i] - '0';
		}
		i++;
	}
	return (k * nb);
}

int	is_all_number(char **str)
{
	int		i;
	int		j;
	long	n;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-' || str[i][j] == '+')
			j++;
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (0);
			j++;
		}
		n = ft_atoi(str[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

int	test_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
	{
	:	return (0);
	}
	if (! is_all_number(av))
		return (0);

	return (1);
}
/*
void	create_philosophers()
{

}*/

int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;

//	test_args(argc, argv);
//	create_philosophers();
//	run_philosophers();
	printf("%d\n",ft_atoi("1234"));
	return 0;
}
