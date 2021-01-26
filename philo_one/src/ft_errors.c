/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:42 by mhufflep          #+#    #+#             */
/*   Updated: 2021/01/26 16:53:55 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char *get_error(int code)
{
	char *errors[10];

	errors[0] = "philo takes 4 or 5 numeric arguments";
	errors[1] = "non numeric or negative argument";
	errors[2] = "there must be at least two philosophers";
	errors[3] = "too long argument";
	errors[4] = "cannot allocate memory for philosophers";
	errors[5] = "cannot create data structure";
	return (errors[code]);
}

int	print_error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, ".\n", 2);
	return (0);
}
