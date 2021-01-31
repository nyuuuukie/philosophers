/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:12:07 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:45:04 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_ull get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	wait_until(t_ull time)
{
	while (get_time() < time)
	{
		usleep(50);
	}
}