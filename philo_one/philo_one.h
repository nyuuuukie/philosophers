/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 03:10:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/23 04:00:14 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>

# include "ft_atoi.h"
  
typedef struct	s_args
{
	unsigned long long philo_num;
	unsigned long long time_to_die;
	unsigned long long time_to_eat;
	unsigned long long time_to_sleep;
	unsigned long long number_of_times;
}				t_args;



#endif