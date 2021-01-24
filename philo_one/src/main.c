/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:47:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/24 18:13:15 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_ull get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, const char *msg)
{
	t_ull timestamp;
	
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->print);
	printf("%llu %lld %s\n", timestamp, philo->num, msg);
	pthread_mutex_unlock(philo->data->print);
}

void	wait_until(t_ull time)
{
	while (get_time() < time)
	{
		usleep(20);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	pthread_mutex_lock(&philo->data->forks[philo->right]);

	philo->last_meal = get_time();
	print_status(philo, "is eating");
	philo->eating_count++;
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

void*	observe(void *ph)
{
	t_philo *philo;
	
	philo = (t_philo *)ph;
	while (1)
	{
		if (philo->last_meal + philo->args->time_to_die > get_time() ||
			philo->data->start_time + philo->args->time_to_die > get_time())
		{
			print_status(philo, "is dead");
			//break;
			//pthread_mutex_lock(philo->data->death);
		}
		usleep(20);
	}
	return (NULL);
}

void*	cycle(void *ph)
{
	//pthread_t	death_thread;
	t_philo		*philo;
	
	philo = (t_philo *)ph;
	
	//pthread_create(&death_thread, NULL, observe, ph);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	//pthread_join(death_thread, NULL);
	return (NULL);
}

t_data	*prepare_data(t_args *args)
{
	t_data		*data;
	t_ull		i;

	data = malloc(sizeof(t_data));
	data->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	data->death = malloc(sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->death, NULL);
	pthread_mutex_init(data->print, NULL);

	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}

int		prepare_philosophers(t_philo *philosophers, t_args *args)
{
	t_data	*data;
	t_ull	i;
	
	i = 0;
	data = prepare_data(args);
	data->start_time = get_time();
	while (i < args->philo_num)
	{
		philosophers[i].data = data;
		philosophers[i].args = args;
		philosophers[i].eating_count = 0;
		philosophers[i].num = i + 1;
		philosophers[i].left = (i + 1) % args->philo_num;
		philosophers[i].right = i - 1;
		i++;
	}
	return (0);
}

int	destroy_philos(t_philo *philos, t_args *args)
{
	t_ull i;
	
	i = 0;
	while (i < args->philo_num)
    {
		pthread_mutex_destroy(&philos[i].data->forks[i]);
		i++;
    }
	pthread_mutex_destroy(philos[0].data->print);
	pthread_mutex_destroy(philos[0].data->death);
	free(philos[0].data->forks);
	free(philos[0].data->print);
	free(philos[0].data->death);
	free(philos[0].data);
	free(philos);
	return (0);
}

int start_simulation(t_args *args)
{
	t_philo		*philosophers;
	pthread_t	threads[args->philo_num];
	t_ull		i;

	philosophers = malloc(sizeof(t_philo) * args->philo_num);
	prepare_philosophers(philosophers, args);
	
	i = 0;
	while (i < args->philo_num)
	{
    	pthread_create(&threads[i], NULL, cycle, (void *)&philosophers[i]);
		i++;
	}

	i = 0;
	while (i < args->philo_num)
    {
		pthread_join(threads[i], NULL);
		i++;
    }

	destroy_philos(philosophers, args);
	return (0);
}

int	get_arguments(int argc, char *argv[], t_args *args)
{
	if (ft_atoi(argv[1], &args->philo_num) == -1 || args->philo_num < 2)
		return (-1);
	if (ft_atoi(argv[2], &args->time_to_die) == -1)
		return (-1);
	if (ft_atoi(argv[3], &args->time_to_eat) == -1)
		return (-1);
	if (ft_atoi(argv[4], &args->time_to_sleep) == -1)
		return (-1);
	if (argc == 6 && ft_atoi(argv[5], &args->number_of_times) == -1)
		return (-1);
	return (0);
}

int main(int argc, char *argv[])
{
	t_args args;

	if (argc == 5 || argc == 6)
	{
		if (get_arguments(argc, argv, &args) == -1)
			printf("Error: Non numeric or negative argument.\n");
		else
		{
			start_simulation(&args);
		}
	}
	else
	{
		printf("Error: philo_one takes 4 or 5 numeric arguments.\n");
	}
	return (0);
}