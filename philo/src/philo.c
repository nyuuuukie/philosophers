#include "philo.h"

int	create_philos(t_philo *philos, int *args)
{
	t_data	*data;
	t_ull	i;
	
	i = 0;
	data = prepare_data(args);
	if (!data)
		return (1);
	while (i < args[0])
	{
		philos[i].data = data;
		philos[i].args = args;
		philos[i].last_time = data->start_time;
		philos[i].num = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % args[0];
		i++;
	}
	return (0);
}

int	destroy_philos(t_philo *philos, int *args)
{
	int res;

	res = 0;
	if (destroy_mutexes(philos[0].data, args))
		res = 1;
	free(philos[0].data->forks);
	free(philos[0].data->print);
	free(philos[0].data->death);
	free(philos[0].data);
	free(philos);
	return (res);
}