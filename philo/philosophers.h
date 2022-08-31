/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:56:10 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 17:35:13 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//#include <bits/types/struct_timeval.h>
# include<sys/time.h>
# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
# include<pthread.h>
# include<unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_ctx {
	int				stop;
	long			start_time;
	int				forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	pthread_mutex_t	printf_lock;
}	t_ctx;

typedef struct s_philo {
	int				name;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	t_ctx			*ctx;
	long			last_meal;
	int				meals;
}	t_philo;

int		ft_atoi(char *str);
int		is_all_number(char **str);
int		test_args(int ac, char **av);
void	get_args(t_ctx *ctx, int ac, char **av);
long	ft_time(void);
long	ft_diff_time(long start_time);
void	ft_usleep(long time);
t_philo	*create_philosophers(t_ctx *ctx);
int		check_dead_philo(t_philo *philos);
void	ft_printf(long timestamp,
			t_philo *philosopher, char *string, int sleep);
void	*destroy_philos(t_philo *philos);

#endif // !PHILOSOPHERS_H
