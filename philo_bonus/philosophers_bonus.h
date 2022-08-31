/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:56:10 by fael-bou          #+#    #+#             */
/*   Updated: 2022/08/31 16:49:45 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

//#include <bits/types/struct_timeval.h>
# include<sys/time.h>
# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
# include<pthread.h>
# include <semaphore.h>
# include<unistd.h>
# define SEM_FORKS "philo_forks"
# define SEM_PRINTF_LOCK "print_lock"
# define SEM_MEALS_NB "meals_nb" 

typedef struct timeval	t_timeval;

typedef struct s_ctx {
	int			stop;
	long		start_time;
	int			forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_nb;
	sem_t		*all_forks;
	sem_t		*all_meals;
	sem_t		*printf_lock;
}	t_ctx;

typedef struct s_philo {
	int				name;
	pthread_t		check;
	pid_t			pid;
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
void	create_philosophers(t_ctx *ctx);
int		check_meals(t_philo *philos);
void	ft_printf(long timestamp,
			t_philo *philosopher, char *string, int sleep);
void	do_child(t_philo *philo);
void	stop_execution(t_philo *philos, int retval);

#endif // !PHILOSOPHERS_BONUS_H
