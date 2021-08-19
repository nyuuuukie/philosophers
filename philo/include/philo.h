#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef unsigned long long	t_ull;
typedef unsigned long		t_ul;

typedef struct s_mutex
{
	pthread_mutex_t	m;
	int				lock;
}				t_mutex;

typedef struct s_data
{
	t_ull		*args;
	t_mutex		*forks;
	t_mutex		*print;
	t_mutex		*count;
	t_mutex		*order;
	t_mutex		*time;
	int			alive;
	int			next;
	t_ull		satisfied;
	time_t		start_t;
	int			(*next_ph)(int, int);
}				t_data;

typedef struct s_philo
{
	t_data		*data;
	int			num;
	int			left;
	int			right;
	time_t		meal_t;
	t_ul		meals;
}				t_philo;

// next.c

int		next(t_philo *philo);
int		next_odd(int id, int max);
int		next_even(int id, int max);

char	*get_error_msg(int code);
int		errno(int code);
int		print_error(char *title);

// print.c
void	print_locked(t_philo *philo, const char *msg);
void	print_die( t_philo *philo, const char *msg);

// time.c
time_t	timer(void);
int		delay(t_data *data, t_ull time);

// parser.c
int		check_args(int argc, t_ull *args);
int		parse_num(char *s, t_ull *num);
int		get_args(int argc, char *argv[], t_ull *args);

// chopsticks.c
void	put_chopsticks(t_philo *philo);
int		take_chopsticks(t_philo *philo);
int		take_chopstick(t_philo *philo, int num);

// mutex.c
int		lock(t_mutex *mutex);
int		unlock(t_mutex *mutex);
int		init_mutexes(t_data *data, t_ull *args);
int		destroy_mutexes(t_data *data, t_ull *args);

// thread.c
int		alloc_threads(pthread_t **arr, int num);
int		create_threads(pthread_t *ths, t_ull ac,
			t_philo *phs, void *(*f)(void *));
int		join_threads(pthread_t *threads, t_ull args);

// philos.c
int		init_philos(t_philo *philos, t_data *data, t_ull *args);
int		destroy_philos(t_philo *philos, t_ull *args);
t_data	*prepare_data(t_ull *args);
void	*clear_data(t_data *data);

/* CYCLE */
void	*cycle(void *ph);
void	*monitor(void *ph);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);

/* UTILS */
int		findlen(char *s);

#endif
