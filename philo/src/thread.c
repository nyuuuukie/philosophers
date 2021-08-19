#include "philo.h"

int	alloc_threads(pthread_t **arr, int num)
{
	pthread_t	*tmp;

	tmp = malloc(sizeof(pthread_t) * num);
	if (!tmp)
		return (1);
	memset(tmp, 0, sizeof(tmp));
	*arr = tmp;
	return (0);
}

int	create_threads(pthread_t *ths, t_ull ac,
	t_philo *phs, void *(*func)(void *))
{
	t_ull	i;

	i = 0;
	while (i < ac)
	{
		if (pthread_create(&ths[i], NULL, func, (void *)&phs[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(pthread_t *threads, t_ull argc)
{
	t_ull	i;

	i = 0;
	while (i < argc)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
