#include "philo.h"

void	print_status(t_philo *philo, const char *msg)
{
	t_ull timestamp;
	
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->print);
	if (philo->data->alive)
		printf("%llu %lld %s\n", timestamp, philo->num, msg);
	pthread_mutex_unlock(philo->data->print);
}