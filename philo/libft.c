/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:43:29 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/27 23:27:22 by fatimzehra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>

int	ft_atoi(char *str)
{
	int	nb;
	int	i;
	int	k;

	nb = 0;
	i = 0;
	k = 1;
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

void	ft_printf(long timestamp, t_philo *philosopher, char *string, int sleep)
{
	if (philosopher->ctx->stop != 0)
		return ;
	pthread_mutex_lock(&philosopher->ctx->printf_lock);
	printf(string, timestamp, philosopher->name);
	pthread_mutex_unlock(&philosopher->ctx->printf_lock);
	if (sleep > 0)
		ft_usleep(sleep);
}
