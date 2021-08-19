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

void	print_die(t_philo *philo, const char *msg)
{
	t_ull	time;

	lock(philo->data->print);
	if (philo->data->alive)
	{
		philo->data->alive = 0;
		time = timer() - philo->data->start_t;
		printf("%llu %d %s\n", time, philo->num, msg);
	}
	unlock(philo->data->print);
}
