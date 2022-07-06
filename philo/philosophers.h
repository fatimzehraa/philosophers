/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:56:10 by fael-bou          #+#    #+#             */
/*   Updated: 2022/07/06 20:44:57 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
# include<pthread.h>

typedef struct s_ctx {
	int			forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_eating_times;
} t_ctx;

typedef struct s_philo {
	int				name;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	
} t_philo;

int		ft_atoi(char *str);
int		is_all_number(char **str);
int		test_args(int ac, char **av);
void	get_args(t_ctx *ctx, int ac, char **av);
void	create_philosophers(t_ctx *ctx, t_philo *philosopher);

#endif // !PHILOSOPHERS_H

