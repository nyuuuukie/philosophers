#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef unsigned long long	t_ull;
typedef pthread_mutex_t 	t_mutex;

typedef struct 	s_data
{
	t_mutex		*forks;
	t_mutex		*death;
	t_mutex		*print;
	int			alive;
	int			satisfied;
	t_ull		start_time;
}				t_data;

typedef struct		s_philo
{
	int 		*args;
	t_data		*data;
	int			num;
	int			left;
	int			right;
	t_ull		last_time;
	int			eating_count;
}				t_philo;


//print.c
void	print_status(t_philo *philo, const char *msg);

//time.c
t_ull	get_time(void);
void	wait_until(t_ull time);

//mutex.c
int		is_locked(pthread_mutex_t *mutex);

//parser.c
int		check_args(int argc, int *args);
int		parse_num(char *s, int *num);
int		get_args(int argc, char *argv[], int *args);


/* MUTEXES */
int		init_mutexes(t_data *data, int *args);
int		destroy_mutexes(t_data *data, int *args);

/* THREADS */
int		create_threads(pthread_t *threads, t_philo *philos);
int		join_threads(pthread_t *threads, int *args);

/* PHILOSOPHERS */
int		create_philos(t_philo *philos, int *args);
int		destroy_philos(t_philo *philos, int *args);
t_data	*prepare_data(int *args);
void	*clear_data(t_data *data);

/* CYCLE */
void*	cycle(void *ph);
void*	observe(void *ph);
void*	dead_check(void *ph);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/* UTILS */
int 	findlen(char *s);

#endif
