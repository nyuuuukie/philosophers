/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:37:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 10:37:49 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_arguments(int argc, char *argv[], t_args *args)
{
	t_ull	*prms[5];
	int 	i;

	i = 1;
	prms[0] = &args->philo_num;
	prms[1] = &args->time_to_die;
	prms[2] = &args->time_to_eat;
	prms[3] = &args->time_to_sleep;
	prms[4] = &args->eating_count_limit;
	*prms[4] = 0;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > 10)
			return (3);	
		if (ft_atoi(argv[i], prms[i - 1]) == -1)
			return (1);
		i++;
	}
	return ((args->philo_num < 2) * 2);
}
