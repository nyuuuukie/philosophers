/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:32:38 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 19:01:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	print_status(philo, "has taken a chopstick");
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	print_status(philo, "has taken a chopstick");
	
	philo->last_meal = get_time();
	print_status(philo, "is eating");
	philo->eating_count++;
	if (philo->eating_count == philo->args->eating_count_limit)
		philo->data->satisfied_count++;
	
	wait_until(philo->last_meal + philo->args->time_to_eat);
	
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
}

void	sleeping(t_philo *philo)
{
	t_args *args;
	
	args = philo->args;
	print_status(philo, "is sleeping");
	wait_until(philo->last_meal + args->time_to_eat + args->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}
