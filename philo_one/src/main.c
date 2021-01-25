/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:47:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/25 16:29:19 by mhufflep         ###   ########.fr       */
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
	if (philo->data->is_alive)
		printf("%llu %lld %s\n", timestamp, philo->num, msg);
	pthread_mutex_unlock(philo->data->print);
}

void	wait_until(t_ull time)
{
	while (get_time() < time)
	{
		usleep(50);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	print_status(philo, "has taken a chopstick");
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	print_status(philo, "has taken a chopstick");
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	
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
			pthread_mutex_unlock(philo->data->death);
			pthread_mutex_lock(philo->data->print);
			usleep(1000 * philo->num);
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
	if (philo->num % 2 == 0)
		wait_until(get_time() + philo->args->time_to_eat);
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

void	*clear_data(t_data *data)
{
	data && data->forks != NULL ? free(data->forks) : NULL;
	data && data->death != NULL ? free(data->death) : NULL;
	data && data->print != NULL ? free(data->print) : NULL;
	data != NULL ? free(data) : NULL;
	return (NULL);
}

void 	init_all_mutexes(t_data *data, t_args *args)
{
	t_ull i;

	i = 0;
	pthread_mutex_init(data->death, NULL);
	pthread_mutex_init(data->print, NULL);
	pthread_mutex_lock(data->death);
	while (i < args->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void 	destroy_all_mutexes(t_data *data, t_args *args)
{
	t_ull i;
	
	i = 0;
	while (i < args->philo_num)
    {
		pthread_mutex_destroy(&data->forks[i]);
		i++;
    }
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->death);
}

t_data	*prepare_data(t_args *args)
{
	t_data		*data;

	if (!(data = malloc(sizeof(t_data))))
		return (clear_data(data));
	data->print = NULL;
	data->death = NULL;
	data->forks = NULL;
	data->is_alive = 1;
	data->satisfied_count = 0;
	data->start_time = get_time();
	if (!(data->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num)))
		return (clear_data(data));
	if (!(data->death = malloc(sizeof(pthread_mutex_t))))
		return (clear_data(data));
	if (!(data->print = malloc(sizeof(pthread_mutex_t))))
		return (clear_data(data));
	init_all_mutexes(data, args);
	return (data);
}

int		create_philosophers(t_philo *philosophers, t_args *args)
{
	t_data	*data;
	t_ull	i;
	
	i = 0;
	data = prepare_data(args);
	if (!data)
		return (1);
	while (i < args->philo_num)
	{
		philosophers[i].data = data;
		philosophers[i].args = args;
		philosophers[i].last_meal = data->start_time;
		philosophers[i].num = i + 1;
		philosophers[i].left = i;
		philosophers[i].right = (i + 1) % args->philo_num;
		i++;
	}
	return (0);
}

int	destroy_philosophers(t_philo *philos, t_args *args)
{
	destroy_all_mutexes(philos[0].data, args);
	free(philos[0].data->forks);
	free(philos[0].data->print);
	free(philos[0].data->death);
	free(philos[0].data);
	free(philos);
	return (0);
}

int create_threads(pthread_t *threads, t_philo *philosophers)
{
	t_ull i;

	i = 0;
	while (i < philosophers[0].args->philo_num)
	{
    	if (pthread_create(&threads[i], NULL, cycle, (void *)&philosophers[i]))
		{
			pthread_mutex_unlock(philosophers[i].data->death);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(pthread_t *threads, t_args *args)
{
	t_ull i;

	i = 0;
	while (i < args->philo_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

int start_simulation(t_args *args)
{
	pthread_t	threads[args->philo_num];
	t_philo		*philosophers;

	if (!(philosophers = malloc(sizeof(t_philo) * args->philo_num)))
		return (-1);
	
	if (create_philosophers(philosophers, args))
		return (1);

	create_threads(threads, philosophers);
	join_threads(threads, philosophers[0].args);
	destroy_philosophers(philosophers, args);
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
	if (argc == 6 && ft_atoi(argv[5], &args->eating_count_limit) == -1)
		return (-1);
	return (0);
}

char *get_error(int code)
{
	char *errors[10];

	errors[0] = "philo takes 4 or 5 numeric arguments";
	errors[1] = "non numeric or negative argument";
	errors[2] = "cannot allocate memory";
	errors[3] = "";
	errors[4] = "";
	errors[5] = "";
	return (errors[code]);
}

int main(int argc, char *argv[])
{
	t_args args;
	int res;

	if (argc == 5 || argc == 6)
	{
		if ((res = get_arguments(argc, argv, &args)) == -1)
			printf("Error: %s.\n", get_error(1));
		else if ((res = start_simulation(&args)) == -1)
			printf("Error: %s.\n", get_error(2));
	}
	else
	{
		printf("Error: %s.\n", get_error(0));
	}
	return (0);
}