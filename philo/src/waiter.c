#include "philo.h"

void request(t_philo *philo)
{
	int prioritated;

	if (is_prior(philo->num) && is_open(num))
	{
		unlock(&data->forks[philo->left]);
		unlock(&data->forks[philo->right]);
	}
	else
	{
		lock(data->forks[num]);
	}
}

//void release(t_philo *philo)
//{
//	int pr = get_next(philo->data->args[0]);

//	{
//	}
//}

int get_next(int max)
{
	static int id;

	id += 2;
	if (id > max)
	{
		if (max % 2)
		{
			id = id % max;
		}
		else if (id % 2)
		{
			id = id % (max - 1);
		}
		else
		{
			id = id % (max + 1);
		}
	}
	return (id);
}