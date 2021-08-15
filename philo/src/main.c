#include "philo.h"

int start_simulation(int *args)
{
	pthread_t	threads[args[0]];
	t_philo		*philos;

	if (!(philos = malloc(sizeof(t_philo) * args[0])))
		return (errno(4));
	if (create_philos(philos, args))
		return (errno(5));
	if (create_threads(threads, philos))
		return (errno(6));
	join_threads(threads, philos[0].args);
	destroy_philos(philos, args);
	return (0);
}

int main(int argc, char **argv)
{
	int code;
	int args[5];

	code = 0;
	if (argc == 5 || argc == 6)
	{
		memset(args, 0, sizeof(args));	
		if (get_args(argc - 1, &argv[1], args))
			print_error();
		else if (check_args(argc - 1, args))
			print_error();
		else if (start_simulation(&args))
			print_error();
	}
	else
	{
		error(8);
		print_error();
	}
	return (0);
}