/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:47:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/23 04:03:38 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned long long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int start_simulation(t_args *args)
{
	(void)args;
	return (0);
}

int	get_arguments(int argc, char *argv[], t_args *args)
{
	if (ft_atoi(argv[1], &args->philo_num) == -1)
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

	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Philo one takes 4 or 5 arguments.\n");
	}
	else
	{
		if (get_arguments(argc, argv, &args) == -1)
			printf("Error: Wrong argument.\n");
		else
			start_simulation(&args);
	}
	return (0);
}