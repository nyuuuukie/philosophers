/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:10:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/23 10:10:05 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long long	ull; 

typedef struct				s_args
{
	ull 					philo_num;
	ull 					time_to_die;
	ull 					time_to_eat;
	ull 					time_to_sleep;
	ull 					number_of_times;
}							t_args;

typedef struct 				s_data
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			*death;
	pthread_mutex_t			*print;
	ull						start_time;
}							t_data;

typedef struct				s_philo
{
	ull						last_eating;
	t_data					*data;
	t_args					*args;
	int						num;
	int						left;
	int						right;
}							t_philo;


int	ft_atoi(char *s, ull *number);

#endif