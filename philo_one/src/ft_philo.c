/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:40:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:45:28 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*clear_data(t_data *data)
{
	data && data->forks != NULL ? free(data->forks) : NULL;
	data && data->death != NULL ? free(data->death) : NULL;
	data && data->print != NULL ? free(data->print) : NULL;
	data != NULL ? free(data) : NULL;
	return (NULL);
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
		return (4);
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
