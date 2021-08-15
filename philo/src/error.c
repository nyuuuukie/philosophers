char *get_error_msg(int code)
{
	char *errors[10];

	errors[0] = "Hint: <philo nums> <time_to_die> <time_to_eat> <time_to_sleep> [eat_limit]";
	errors[1] = "argument cannot be empty";
	errors[2] = "non numeric or negative argument";
	errors[3] = "argument value overflows integer max";

	errors[4] = "cannot allocate memory for philosophers";
	errors[5] = "cannot allocate memory for data";
	errors[6] = "cannot create threads";

	errors[7] = "meaningless";
	return (errors[code]);
}

int	print_error()
{
	char *msg; 
    
    msg = get_error_msg(errno(0));
    write(2, "Error: ", 7);
	write(2, msg, findlen(msg));
	write(2, ".\n", 2);
	return (0);
}

int errno(int code)
{
    static int err;

    if (code != 0)
        err = code;

    return err;
}
