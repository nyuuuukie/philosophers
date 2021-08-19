int	findlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != 0)
	{
		i++;
	}
	return (i);
}
