#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef unsigned long long	t_ull;
typedef unsigned long t_ul;
//typedef pthread_mutex_t 	t_mutex;

typedef enum e_res
{
	ACCEPT = 0,
	REJECT = 1
}			t_res;

typedef struct	s_mutex
{
	pthread_mutex_t m;
	int lock;
}				t_mutex;

typedef struct 	s_data
{
	t_ull		*args;
	t_mutex		*forks;
	t_mutex		*print;
	t_mutex		*count;
	t_mutex		*waiter;
	int			alive;
	int			prime;
	t_ull		satisfied;
	time_t		start_time;
}				t_data;

typedef struct		s_philo
{
	t_data		*data;
	int			num;
	int			left;
	int			right;
	time_t		last_time;
	t_ul		meals;
}				t_philo;

//t_philo *philo_ref(t_philo *philo);
//int	is_died(t_philo *philo);

//void	print_die(t_philo *philo, const char *msg);
int lock(t_mutex *mutex);
int unlock(t_mutex *mutex);

//int	try_lock_forks(t_philo *philo);

char	*get_error_msg(int code);
int		errno(int code);
int		print_error(char *title);

//print.c
void	print_locked(t_philo *philo, const char *msg);

//time.c
t_ull	get_time(void);
int		delay(t_ull time);
void delay_mcs(t_ull time);

//mutex.c
//int		is_locked(pthread_mutex_t *mutex);

//parser.c
int		check_args(int argc, t_ull *args);
int		parse_num(char *s, t_ull *num);
int		get_args(int argc, char *argv[], t_ull *args);


/* MUTEXES */
int		init_mutexes(t_data *data, t_ull *args);
int		destroy_mutexes(t_data *data, t_ull *args);

/* THREADS */
int create_threads(pthread_t *threads, t_ull argc, t_philo *phs, void *(*func)(void *));
//int		create_threads(pthread_t *threads, t_philo *philos);
int		join_threads(pthread_t *threads, t_ull args);

/* PHILOSOPHERS */
int		init_philos(t_philo *philos, t_data *data, t_ull *args);
int		destroy_philos(t_philo *philos, t_ull *args);
t_data	*prepare_data(t_ull *args);
void	*clear_data(t_data *data);

void	print_eat(t_philo *philo, const char *msg);


/* CYCLE */
void*	cycle(void *ph);
void*	monitor(void *ph);

//void*	dead_check(void *ph);
//int		eating(t_philo *philo);
//int		sleeping(t_philo *philo);
//int		thinking(t_philo *philo);

/* UTILS */
int 	findlen(char *s);

#endif
