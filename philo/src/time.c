#include "philo.h"

time_t	timer(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	delay(t_data *data, t_ull time)
{
	t_ull	current;

	current = timer();
	while (timer() - current < time)
	{
		if (!data->alive)
			return (1);
		usleep(100);
	}
	return (0);
}
