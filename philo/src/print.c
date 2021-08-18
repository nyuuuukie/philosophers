#include "philo.h"

void	print_locked(t_philo *philo, const char *msg)
{
	if (!philo->data->alive)
		return ;
	lock(philo->data->print);
	t_ull time = get_time() - philo->data->start_time;
	printf("%llu %d %s\n", time, philo->num, msg);
	unlock(philo->data->print);
}
