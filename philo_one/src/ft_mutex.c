/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:33:36 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 10:32:46 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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