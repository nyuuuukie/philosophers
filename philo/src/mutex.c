#include "philo.h"

int 	init_mutexes(t_data *data, t_ull *args)
{
	t_ull i;

	i = 0;
	if (pthread_mutex_init(&data->print->m, NULL))
		return (1);
	if (pthread_mutex_init(&data->waiter->m, NULL))
		return (1);
	if (pthread_mutex_init(&data->count->m, NULL))
		return (1);
	data->waiter->lock = 0;
	data->print->lock = 0;
	data->count->lock = 0;
	while (i < args[0])
	{
		data->forks[i].lock = 0;
		if (pthread_mutex_init(&data->forks[i].m, NULL))
			return (1);
		i++;
	}
	return (0);
}

int 	destroy_mutexes(t_data *data, t_ull *args)
{
	t_ull i;

	i = 0;
	while (i < args[0])
    {
		if (pthread_mutex_destroy(&data->forks[i].m))
			return (1);
		i++;
    }
	if (pthread_mutex_destroy(&data->print->m))
		return (1);
	if (pthread_mutex_destroy(&data->waiter->m))
		return (1);
	if (pthread_mutex_destroy(&data->count->m))
		return (1);
	return (0);
}