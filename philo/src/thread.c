#include "philo.h"

int create_threads(pthread_t *threads, t_ull argc, t_philo *phs, void *(*func)(void *))
{
	t_ull i;

	i = 0;
	while (i < argc)
	{
    	if (pthread_create(&threads[i], NULL, func, (void *)&phs[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(pthread_t *threads, t_ull argc)
{
	t_ull i;

	i = 0;
	while (i < argc)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}