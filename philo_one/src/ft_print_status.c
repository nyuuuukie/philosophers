/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:20:57 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:45:04 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, const char *msg)
{
	t_ull timestamp;
	
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->print);
	if (philo->data->is_alive)
		printf("%llu %lld %s\n", timestamp, philo->num, msg);
	pthread_mutex_unlock(philo->data->print);
}