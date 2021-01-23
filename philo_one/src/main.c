/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:47:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/23 10:59:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

ull get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, const char *msg)
{
	ull timestamp;
	
	pthread_mutex_lock(philo->data->print);
	timestamp = get_time() - philo->data->start_time;
	printf("%llu %d %s\n", timestamp, philo->num, msg);
	pthread_mutex_unlock(philo->data->print);
}

void	wait_until(ull time)
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

	philo->last_eating = get_time();
	print_status(philo, "is eating");
	wait_until(philo->last_eating + philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
}

void	sleeping(t_philo *philo)
{
	t_args *args = philo->args;
	print_status(philo, "is sleeping");
	wait_until(philo->last_eating + args->time_to_eat + args->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void*	observe(void *ph)
{
	
}

void*	cycle(void *ph)
{
	t_philo *philo;
	
	pthread_t death_thread;
	pthread_create(&death_thread, NULL, observe, ph);
	philo = (t_philo *)ph;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

t_data	prepare_data(t_args *args)
{
	t_data	data;
	ull		i;

	data.start_time = get_time();
	data.forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	data.death = malloc(sizeof(pthread_mutex_t));
	data.print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data.death, NULL);
	pthread_mutex_init(data.print, NULL);

	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	return (data);
}

int start_simulation(t_args *args)
{
	pthread_t threads[args->philo_num];
	t_philo philosophers[args->philo_num];
	t_data data;
	ull i;

	data = prepare_data(args);
	
	i = 0; 
	while (i < args->philo_num)
	{
		philosophers[i].data = &data;
		philosophers[i].args = args;
		philosophers[i].num = i + 1;
		philosophers[i].left = (i + 1) % args->philo_num;
		philosophers[i].right = i - 1;
		i++;
	}

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
		pthread_mutex_destroy(&data.forks[i]);
		i++;
    }
	pthread_mutex_destroy(data.print);
	pthread_mutex_destroy(data.death);
	free(data.forks);
	return (0);
}

int	get_arguments(int argc, char *argv[], t_args *args)
{
	if (ft_atoi(argv[1], &args->philo_num) == -1 || args->philo_num == 1)
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