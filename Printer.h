#ifndef PRINTER
#define PRINTER

#include <string>

#include "MDPLibrary/SharedPointer.h"

void retreat(long depth);
void print(SharedPointer<long>, long depth = 0);
void print(long, long depth = 0);
void print(SharedPointer<std::string>, long depth = 0);
void print(std::string, long depth = 0);

#include "Printer.cpp"

#endif