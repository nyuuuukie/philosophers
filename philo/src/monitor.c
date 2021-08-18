#include "philo.h"

void	*monitor(void *ph)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)ph;
	data = philo->data;
	while (data->alive)
	{
		if (data->satisfied == data->args[4])
		{
			data->alive = 0;
			return (NULL);
		}
		
		lock(data->waiter);
		if (get_time() - philo->last_time > data->args[1])
		{
			print_locked(philo, "died");
			data->alive = 0;
		}
		unlock(data->waiter);
	}
	return (NULL);
}
