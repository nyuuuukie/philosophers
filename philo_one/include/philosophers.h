/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:10:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 18:42:52 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include "philo_struct.h"

/* MUTEXES */
void 	init_all_mutexes(t_data *data, t_args *args);
void 	destroy_all_mutexes(t_data *data, t_args *args);

/* THREADS */
int		create_threads(pthread_t *threads, t_philo *philosophers);
int		join_threads(pthread_t *threads, t_args *args);

/* PHILOSOPHERS */
int		create_philosophers(t_philo *philosophers, t_args *args);
int		destroy_philosophers(t_philo *philos, t_args *args);
t_data	*prepare_data(t_args *args);
void	*clear_data(t_data *data);

/* CYCLE */
void*	cycle(void *ph);
void*	observe(void *ph);
void*	dead_check(void *ph);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/* UTILS */
int 	ft_strlen(char *s);
int		ft_atoi(char *s, t_ull *number);

/* TIME */
t_ull	get_time(void);
void	wait_until(t_ull time);

/* ARGUMENTS */
int		get_arguments(int argc, char *argv[], t_args *args);

/* PRINT & ERRORS */
void	print_status(t_philo *philo, const char *msg);
int		print_error(char *msg);
char	*get_error(int code);

#endif