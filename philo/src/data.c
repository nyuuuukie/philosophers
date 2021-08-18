#include "philo.h"

void	*clear_data(t_data *data)
{
	if (data && data->forks != NULL)
		free(data->forks);
	if (data && data->waiter != NULL)
		free(data->waiter);
	if (data && data->print != NULL)
		free(data->print);
	if (data != NULL)
		free(data);
	return (NULL);
}

static t_data *alloc_data(t_ull *args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data)
	{
		memset(data, 0, sizeof(t_data));
		data->forks = malloc(sizeof(t_mutex) * args[0]);
		data->print = malloc(sizeof(t_mutex));
		data->count = malloc(sizeof(t_mutex));
		data->time = malloc(sizeof(t_mutex));
		data->waiter = malloc(sizeof(t_mutex));
		if (!data->time || !data->forks || !data->print || 
			!data->waiter || !data->count)
			return (clear_data(data));
	}
	return (data);
}	

t_data	*prepare_data(t_ull *args)
{
	t_data	*data;

	data = alloc_data(args);
	if (data)
	{
		data->alive = 1;
		data->prime = 1;
		data->args = args;
		if (init_mutexes(data, args))
			return (clear_data(data));
	}	
	return (data);
}
