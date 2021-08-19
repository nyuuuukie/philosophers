#include "philo.h"

void	*monitor(void *ph)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ph;
	data = philo->data;
	lock(data->time);
	while (data->alive && timer() - philo->meal_t <= (time_t)data->args[1])
	{
		unlock(data->time);
		usleep(100);
		lock(data->time);
	}
	if (data->alive)
	{
		print_die(philo, "died");
		data->alive = 0;
	}
	unlock(data->time);
	return (NULL);
}
