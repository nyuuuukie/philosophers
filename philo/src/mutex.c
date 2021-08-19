#include "philo.h"

int	lock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->m);
	mutex->lock = 1;
	return (0);
}

int	unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->m);
	mutex->lock = 0;
	return (0);
}

int	init_mutexes(t_data *data, t_ull *args)
{
	t_ull	i;

	i = 0;
	if (pthread_mutex_init(&data->print->m, NULL))
		return (1);
	if (pthread_mutex_init(&data->order->m, NULL))
		return (1);
	if (pthread_mutex_init(&data->count->m, NULL))
		return (1);
	if (pthread_mutex_init(&data->time->m, NULL))
		return (1);
	data->order->lock = 0;
	data->print->lock = 0;
	data->count->lock = 0;
	data->time->lock = 0;
	while (i < args[0])
	{
		data->forks[i].lock = 0;
		if (pthread_mutex_init(&data->forks[i].m, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	destroy_mutexes(t_data *data, t_ull *args)
{
	t_ull	i;

	i = 0;
	while (i < args[0])
	{
		if (data->forks[i].lock)
			unlock(&data->forks[i]);
		if (pthread_mutex_destroy(&data->forks[i].m))
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->print->m))
		return (1);
	if (pthread_mutex_destroy(&data->order->m))
		return (1);
	if (pthread_mutex_destroy(&data->count->m))
		return (1);
	if (pthread_mutex_destroy(&data->time->m))
		return (1);
	return (0);
}
