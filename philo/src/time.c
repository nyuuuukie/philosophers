#include "philo.h"

t_ull get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_ull get_time_mcs(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	delay_mcs(t_ull time)
{
	t_ull current;

	current = get_time_mcs();
	while (current + time < get_time_mcs())
	{
		usleep(time / 10);
	}
}

int	delay(t_ull time)
{
	t_ull current;

	current = get_time();
	while (get_time() - current < time)
	{
		usleep(10);
	}
	return (0);
}