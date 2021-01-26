#include <stdlib.h>
#include <limits.h>

#include <iostream>

struct data
{
	std::string first;
	int num;
	std::string second;
};

void *serialize(void)
{
	data *d = new data();

	d->first = "abcdefgh";
	d->second = "klmnoprs";
	d->num = 42;

	return (d);
}

int main(void)
{
	int *ptr = (int *)malloc(120);
	data *d = (data *)serialize();
	printf("%lu\n", sizeof(*d));
	return (0);
}