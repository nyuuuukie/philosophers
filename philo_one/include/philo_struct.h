/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:15:30 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:17:11 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef unsigned long long	t_ull; 

typedef struct				s_args
{
	t_ull 					philo_num;
	t_ull 					time_to_die;
	t_ull 					time_to_eat;
	t_ull 					time_to_sleep;
	t_ull 					eating_count_limit;
}							t_args;

typedef struct 				s_data
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			*death;
	pthread_mutex_t			*print;
	t_ull					is_alive;
	t_ull					start_time;
	t_ull					satisfied_count;
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

#endif