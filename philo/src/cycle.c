#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	print_status(philo, "has taken a chopstick");
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	print_status(philo, "has taken a chopstick");

	philo->last_time = get_time();
	print_status(philo, "is eating");
	philo->eating_count++;
	if (philo->eating_count == philo->args[4])
		philo->data->satisfied++;

	wait_until(philo->last_time + philo->args[2]);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	wait_until(philo->last_time + philo->args[2] + philo->args[3]);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void*	cycle(void *ph)
{
	t_philo		*philo;
	
	philo = (t_philo *)ph;
	//if (philo->num % 2 == 0)
	//	wait_until(get_time() + philo->args->time_to_eat);
	while (philo->data->alive)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
