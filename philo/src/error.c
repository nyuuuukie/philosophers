#include "philo.h"

char	*get_error_msg(int code)
{
	char	*errors[8];

	errors[0] = "<philos> <t_die> <t_eat> <t_sleep> [meals_limit]";
	errors[1] = "argument cannot be empty";
	errors[2] = "non numeric or negative argument";
	errors[3] = "argument value overflows integer";
	errors[4] = "zero argument specified";
	errors[5] = "cannot allocate memory for data";
	errors[6] = "cannot allocate memory for philosophers";
	errors[7] = "cannot create threads";
	return (errors[code % 8]);
}

int	errno(int code)
{
	static int	err;

	if (code != 0)
		err = code;
	return (err);
}

int	print_error(char *title)
{
	char	*msg;
	int		err;

	err = errno(0);
	msg = get_error_msg(err);
	write(2, title, findlen(title));
	write(2, ": ", 2);
	write(2, msg, findlen(msg));
	write(2, "\n", 1);
	return (err);
}
