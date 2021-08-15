#include "philo.h"

void	*clear_data(t_data *data)
{
	if (data && data->forks != NULL)
		free(data->forks);
	if (data && data->death != NULL)
		free(data->death);
	if (data && data->print != NULL)
		free(data->print);
	if (data != NULL)
		free(data);
	return (NULL);
}

t_data	*prepare_data(int *args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (clear_data(data));
	memset(data, 0, sizeof(t_data));
	data->alive = 1;
	data->start_time = get_time();
	data->forks = malloc(sizeof(t_mutex) * args[0]);
	data->death = malloc(sizeof(t_mutex));
	data->print = malloc(sizeof(t_mutex));
	if (!data->forks || !data->forks || !data->forks)
		return (clear_data(data));
	if (init_mutexes(data, args))
		return (clear_data(data));
	return (data);
}
