#include "philosophers.h"

long	ft_time()
{
	long	time;
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	ft_diff_time(long start_time)
{
	long		timestamp_in_ms;

	timestamp_in_ms = ft_time() - start_time;
	if (timestamp_in_ms <  0)
	{
		printf("%ld - %ld\n", start_time, ft_time());
	}
	return (timestamp_in_ms);
}

void	ft_usleep(long time)
{
	unsigned int	first_sleep;
	unsigned int	time_left;
	long			starting_time;

	starting_time = ft_time();
	first_sleep = time * 0.95;
	time_left = time - first_sleep;
	usleep(first_sleep * 1000);
	while (time_left)
	{
		if (ft_time() - starting_time >= time)
			break ;
	}
}

