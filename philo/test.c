int main()
{
    int id;

	id = 1;
	int args[6] = {6};
	while (1)
	{
		printf("%d,", id);
		id += 2;
		if (id > args[0])
		{
			if (args[0] % 2)
			{
				id = id % args[0];
			}
			else if (id % 2)
			{
				id = id % (args[0] - 1);
			}
			else
			{
				id = id % (args[0] + 1);
			}
		}
	}

    return 0;
}
