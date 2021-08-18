#include "philo.h"

int	init_philos(t_philo *philos, t_data *data, t_ull *args)
{
	t_ull i;
	
	i = 0;
	while (i < args[0])
	{
		philos[i].data = data;
		philos[i].last_time = data->start_time;
		philos[i].num = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % args[0];
		i++;
	}
	return (0);
}

int	destroy_philos(t_philo *philos, t_ull *args)
{
	int res;

	res = destroy_mutexes(philos[0].data, args);
	free(philos[0].data->forks);
	free(philos[0].data->print);
	free(philos[0].data->count);
	free(philos[0].data->waiter);
	free(philos[0].data);
	free(philos);
	return (res);
}