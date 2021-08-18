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


void put_chopsticks(t_philo *philo)
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

int	take_chopstick(t_philo *philo, int num)
{
	lock(&philo->data->forks[num]);
	print_locked(philo, "has taken a chopstick");
	if (!philo->data->alive)
	{
		put_chopsticks(philo);
		return (1);
	}
	return (0);
}

int take_chopsticks(t_philo *philo)
{
	if (philo->num % 2)
	{
		if (take_chopstick(philo, philo->left))
			return (1);
		if (take_chopstick(philo, philo->right))
			return (1);
	}
	else
	{
		if (take_chopstick(philo, philo->right))
			return (1);
		if (take_chopstick(philo, philo->left))
			return (1);
	}
	return (0);
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
	while (philo->data->alive)
	{
		if (philo->num == philo->data->prime)
		{
			if (take_chopsticks(philo))
				break ;

			lock(philo->data->waiter);
			philo->data->prime = get_next(philo);
			unlock(philo->data->waiter);

			lock(philo->data->time);
			philo->last_time = get_time();
			unlock(philo->data->time);
			
			print_locked(philo, "is eating");
			if (delay(philo->data, philo->data->args[2]))
			{
				put_chopsticks(philo);
				break ;
			}
			
			put_chopsticks(philo);
			
			if (count_meals(philo))
				break;

			print_locked(philo, "is sleeping");
			if (delay(philo->data, philo->data->args[3]))
				break ;
			print_locked(philo, "is thinking");
		}
		//usleep(100);
	}
	return (NULL);
}
