#include "philo.h"

void	*monitor(void *ph)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)ph;
	data = philo->data;
	lock(data->time);
	while (data->alive)
	{
		if (get_time() - philo->last_time > (time_t)data->args[1])
		{
			print_locked(philo, "died");
			data->alive = 0;
			break;
		}
		unlock(data->time);
		usleep(50);
		lock(data->time);
	}
	unlock(data->time);
	return (NULL);
}
