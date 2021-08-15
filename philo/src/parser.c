#include "philo.h"

int check_args(int argc, int *args)
{
	int i;

	i = 0;
	if (args[0] < 2)
		return (errno(7));
	while (i < argc)
	{
		if (args[i] == 0)
			return (errno(4));
		i++;
	}
	return (0);
}

int parse_num(char *s, int *num)
{
	unsigned long long res;

	res = 0;
	while (*s == ' ' || *s == '\n')
		s++;
	if (*s == '\0')
		return (-1);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-2);
		if (res * 10 + (*s - '0') < 0)
			return (-3);
		res = res * 10 + (*s - '0');
		s++;
	}
	*num = res;
	return (0);
}

int	get_args(int argc, char *argv[], int *args)
{
	int i;
	int res;

	i = 0;
	while (i < argc)
	{
		res = parse_num(argv[i], &args[i]);
		if (res != 0)
			break ;
		i++;
	}
	return (errno(res));
}