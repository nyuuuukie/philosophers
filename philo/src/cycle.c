#include "philo.h"

int	count_meals(t_philo *philo)
{
	lock(philo->data->count);
	philo->meals++;
	if ((t_ull)philo->meals == philo->data->args[4])
	{
		philo->data->satisfied++;
	}
	unlock(philo->data->count);
	if (philo->data->satisfied >= philo->data->args[0])
	{
		philo->data->alive = 0;
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (take_chopsticks(philo))
		return (0);
	lock(philo->data->order);
	philo->data->next = next(philo);
	unlock(philo->data->order);
	lock(philo->data->time);
	philo->meal_t = timer();
	unlock(philo->data->time);
	if (!philo->data->alive)
		return (0);
	print_locked(philo, "is eating");
	if (!philo->data->alive)
		return (0);
	delay(philo->data, philo->data->args[2]);
	if (!philo->data->alive)
		return (0);
	put_chopsticks(philo);
	count_meals(philo);
	if (!philo->data->alive)
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!philo->data->alive)
		return (0);
	print_locked(philo, "is sleeping");
	delay(philo->data, philo->data->args[3]);
	if (!philo->data->alive)
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (!philo->data->alive)
		return (0);
	print_locked(philo, "is thinking");
	if (!philo->data->alive)
		return (0);
	return (1);
}

void	*cycle(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (philo->data->alive)
	{
		if (philo->num == philo->data->next)
		{
			if (!eating(philo))
			{
				put_chopsticks(philo);
				break ;
			}
			if (!sleeping(philo))
				break ;
			if (!thinking(philo))
				break ;
		}
		usleep(500);
	}
	return (NULL);
}
