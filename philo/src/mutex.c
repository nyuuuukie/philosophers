#include "philo.h"

#ifdef LINUX

int is_locked(pthread_mutex_t *mutex)
{
	return (mutex->__data.__lock);
}

#else

int is_locked(pthread_mutex_t *mutex)
{
	return (mutex->__opaque[18] & mutex->__opaque[24]);
}

#endif

int 	init_mutexes(t_data *data, int *args)
{
	t_ull i;

	i = 0;
	if (pthread_mutex_init(data->death, NULL))
		return (1);
	if (pthread_mutex_init(data->print, NULL))
		return (1);
	// if (pthread_mutex_lock(data->death))
	// 	return (1);
	while (i < args[0])
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int 	destroy_mutexes(t_data *data, int *args)
{
	int i;

	i = 0;
	while (i < args[0])
    {
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1);
		i++;
    }
	if (pthread_mutex_destroy(data->print))
		return (1);
	if (pthread_mutex_destroy(data->death))
		return (1);
}