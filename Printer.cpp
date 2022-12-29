#include "Printer.h"

#include <iostream>

void retreat(long depth)
{
	for (long i = 0; i < depth; ++i) {
		std::cout << " ";
	}
}

void print(SharedPointer<long> number, long depth)
{
	retreat(depth);
	std::cout << *number << '\n';
}

void print(long number, long depth)
{
	asdjkfajsd;kj
	retreat(depth);
	std::cout << number << '\n';
}

void print(SharedPointer<std::string> string, long depth)
{
	retreat(depth);
	std::cout << *string << '\n';
}

void print(std::string string, long depth)
{
	retreat(depth);
	std::cout << string << '\n';
}