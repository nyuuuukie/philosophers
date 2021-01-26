/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:10:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 16:54:06 by mhufflep         ###   ########.fr       */
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

/* MUTEXES */
void 	init_all_mutexes(t_data *data, t_args *args);
void 	destroy_all_mutexes(t_data *data, t_args *args);

/* THREADS */
int create_threads(pthread_t *threads, t_philo *philosophers);
int	join_threads(pthread_t *threads, t_args *args);

void*	cycle(void *ph);

/* UTILS */
int	ft_atoi(char *s, t_ull *number);
int ft_strlen(char *s);


int	get_arguments(int argc, char *argv[], t_args *args);

/* ERRORS */
char	*get_error(int code);
int		print_error(char *msg);

#endif