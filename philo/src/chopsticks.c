#include "philo.h"

void	put_chopsticks(t_philo *philo)
{
	unlock(&philo->data->forks[philo->left]);
	unlock(&philo->data->forks[philo->right]);
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

int	take_chopsticks(t_philo *philo)
{
	if (take_chopstick(philo, philo->left))
		return (1);
	if (philo->left == philo->right)
	{
		delay(philo->data, 2 * philo->data->args[1]);
		return (1);
	}
	if (take_chopstick(philo, philo->right))
		return (1);
	return (0);
}
