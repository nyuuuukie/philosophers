#include "philo.h"

void	print_locked(t_philo *philo, const char *msg)
{
	t_ull	time;

	lock(philo->data->print);
	if (philo->data->alive)
	{
		time = timer() - philo->data->start_t;
		printf("%llu %d %s\n", time, philo->num, msg);
	}
	unlock(philo->data->print);
}
