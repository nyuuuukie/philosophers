#include "philo.h"

int lock(t_mutex *mutex)
{	
	pthread_mutex_lock(&mutex->m);
	mutex->lock = 1;
	return (0);
}

int unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->m);
	mutex->lock = 0;
	return (0);
}

int get_next(t_philo *philo)
{
	int id;
	int max;

	id = philo->data->prime + 2;
	max = philo->data->args[0];
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

void take_chopsticks(t_philo *philo)
{
	
	lock(&philo->data->forks[philo->left]);
	print_locked(philo, "has taken a chopstick");
	lock(&philo->data->forks[philo->right]);
	print_locked(philo, "has taken a chopstick");
	
	lock(philo->data->waiter);
	philo->data->prime = get_next(philo);
	unlock(philo->data->waiter);
	
}

void release_chopsticks(t_philo *philo)
{
	//lock(philo->data->waiter);
	if (philo->num % 2 == 0)
	{
		unlock(&philo->data->forks[philo->right]);
		unlock(&philo->data->forks[philo->left]);
	}
	else
	{
		unlock(&philo->data->forks[philo->left]);
		unlock(&philo->data->forks[philo->right]);
	}
	//unlock(philo->data->waiter);
}

int	count_meals(t_philo *philo)
{
	int res;

	res = 0;
	lock(philo->data->count);
	philo->meals++;
	if ((t_ull)philo->meals == philo->data->args[4])
	{
		philo->data->satisfied++;
		if (philo->data->satisfied >= philo->data->args[0])
		{
			res = 1;
			philo->data->alive = 0;
		}
	}
	unlock(philo->data->count);
	return (res);
}

void*	cycle(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	//if (philo->num % 2)
	//	usleep(philo->data->args[1] / 2);
	while (philo->data->alive)
	{
		if (philo->num == philo->data->prime)
		{
			take_chopsticks(philo);

			//lock(philo->data->waiter);
			philo->last_time = get_time();
			//unlock(philo->data->waiter);
			
			print_locked(philo, "is eating");
			delay(philo->data->args[2]);
			
			release_chopsticks(philo);
			
			if (count_meals(philo))
				break;

			print_locked(philo, "is sleeping");
			delay(philo->data->args[3]);
			print_locked(philo, "is thinking");
		}
	}
	return (NULL);
}
