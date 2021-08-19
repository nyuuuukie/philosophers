#include "philo.h"

int	start_simulation(t_ull *args)
{
	pthread_t	*cycles;
	pthread_t	*monitors;
	t_data		*data;
	t_philo		*philos;

	data = prepare_data(args);
	if (!data)
		return (errno(5));
	philos = malloc(sizeof(t_philo) * args[0]);
	if (!philos)
		return (errno(6));
	data->start_t = timer();
	init_philos(philos, data, args);
	if (alloc_threads(&cycles, args[0]))
		return (errno(7));
	if (alloc_threads(&monitors, args[0]))
		return (errno(7));
	if (create_threads(cycles, args[0], philos, cycle))
		return (errno(7));
	if (create_threads(monitors, args[0], philos, monitor))
		return (errno(7));
	join_threads(cycles, args[0]);
	join_threads(monitors, args[0]);
	destroy_philos(philos, args);
	return (0);
}

int	main(int argc, char **argv)
{
	t_ull	args[5];

	if (argc == 5 || argc == 6)
	{
		memset(args, 0, sizeof(args));
		if (get_args(argc - 1, &argv[1], args))
			return (print_error("Parse error"));
		else if (check_args(argc - 1, args))
			return (print_error("Check error"));
		else if (start_simulation(args))
			return (print_error("Exec error"));
	}
	else
		return (print_error("Hint"));
}
