#include "philo.h"

unsigned long long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	wait_until(unsigned long long time)
{
	while (get_time() < time)
	{
		usleep(100);
	}
}