/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:47:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 19:03:06 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void*	dead_check(void *ph)
{
	t_philo *philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(philo->data->death);
	philo->data->is_alive = 0;
	pthread_mutex_unlock(philo->data->death);
	return (NULL);
}

void*	observe(void *ph)
{
	t_philo *philo;
	
	philo = (t_philo *)ph;
	while (1)
	{
		if (philo->data->satisfied_count == philo->args->philo_num)
		{
			print_status(philo, "simulation stoped");
			//pthread_mutex_lock(philo->data->print);
			pthread_mutex_unlock(philo->data->death);
			//usleep(1000 * philo->num);
			pthread_mutex_unlock(philo->data->print);
			break ;
		}
		if (philo->last_meal + philo->args->time_to_die < get_time())
		{
			pthread_mutex_unlock(philo->data->death);
			print_status(philo, "died");
			break ;
		}
		usleep(20);
	}
	return (NULL);
}

void*	cycle(void *ph)
{
	pthread_t	death_thread;
	pthread_t	stop_simulation;
	t_philo		*philo;
	
	philo = (t_philo *)ph;
	
	pthread_create(&death_thread, NULL, observe, ph);
	pthread_create(&stop_simulation, NULL, dead_check, ph);
	//if (philo->num % 2 == 0)
	//	wait_until(get_time() + philo->args->time_to_eat);
	while (philo->data->is_alive)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(death_thread, NULL);
	pthread_join(stop_simulation, NULL);
	return (NULL);
}

int start_simulation(t_args *args)
{
	pthread_t	threads[args->philo_num];
	t_philo		*philosophers;

	if (!(philosophers = malloc(sizeof(t_philo) * args->philo_num)))
		return (4);
	if (create_philosophers(philosophers, args))
		return (5);
	if (create_threads(threads, philosophers))
		return (6);
	join_threads(threads, philosophers[0].args);
	destroy_philosophers(philosophers, args);
	return (0);
}

int main(int argc, char *argv[])
{
	t_args	args;
	int		code;

	code = 0;
	if (argc == 5 || argc == 6)
	{
		if ((code = get_arguments(argc, argv, &args)))
			print_error(get_error(code));
		else if ((code = start_simulation(&args)))
			print_error(get_error(code));
	}
	else
	{
		print_error(get_error(code));
	}
	return (0);
}