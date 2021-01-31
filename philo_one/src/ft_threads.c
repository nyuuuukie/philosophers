/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:33:10 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:57:02 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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