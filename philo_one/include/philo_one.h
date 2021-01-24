/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:10:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/24 18:14:17 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long long	t_ull; 

typedef struct				s_args
{
	t_ull 					philo_num;
	t_ull 					time_to_die;
	t_ull 					time_to_eat;
	t_ull 					time_to_sleep;
	t_ull 					number_of_times;
}							t_args;

typedef struct 				s_data
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			*death;
	pthread_mutex_t			*print;
	t_ull					start_time;
}							t_data;

typedef struct				s_philo
{
	t_args					*args;
	t_data					*data;
	t_ull					num;
	t_ull					left;
	t_ull					right;
	t_ull					last_meal;
	t_ull					eating_count;
}							t_philo;


int	ft_atoi(char *s, t_ull *number);

#endif