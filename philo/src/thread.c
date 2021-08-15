#include "philo.h"

int create_threads(pthread_t *threads, t_philo *philos)
{
	t_ull i;

	i = 0;
	while (i < philos[0].args[0])
	{
    	if (pthread_create(&threads[i], NULL, cycle, (void *)&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(pthread_t *threads, int *args)
{
	t_ull i;

	i = 0;
	while (i < args)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}