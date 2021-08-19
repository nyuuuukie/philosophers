#include "philo.h"

int	next(t_philo *philo)
{
	int	id;
	int	max;

	id = philo->data->next + 2;
	max = philo->data->args[0];
	if (max == 2)
		return ((id % 2) + 1);
	else if (id > max)
	{
		if (max % 2)
			id = id % max;
		else if (id % 2)
			id = id % (max - 1);
		else
			id = id % (max + 1);
	}
	return (id);
}
