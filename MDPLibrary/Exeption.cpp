#include "Exeption.h"

#include <iostream>

DefaultExeption::DefaultExeption(
	SharedPointer<Traceback> traceback,
	SharedPointer<Description> description,
	SharedPointer<Optional<SharedPointer<Exeption>>> lowerExeption
)
: _traceback {traceback}, _description {description}, _lowerExeption {lowerExeption}
{
}

DefaultExeption::DefaultExeption(SharedPointer<Traceback> traceback, SharedPointer<Description> description)
: DefaultExeption(traceback, description, new Optional<SharedPointer<Exeption>>)
{
}

void DefaultExeption::baseProcess()
{
	_traceback->print();
	_description->print();
}

SharedPointer<Traceback> DefaultExeption::traceback()
{
	return _traceback;
}

SharedPointer<Description> DefaultExeption::description()
{
	return _description;
}

SharedPointer<Optional<SharedPointer<Exeption>>> DefaultExeption::lowerExeption()
{
	return _lowerExeption;
}

DefaultTraceback::DefaultTraceback(SharedPointer<std::string> stringTraceback)
: _stringTraceback {stringTraceback}
{
}

void DefaultTraceback::print()
{
	std::cout << *_stringTraceback << '\n';
}

DefaultDescription::DefaultDescription(SharedPointer<std::string> stringDescription)
: _stringDescription {stringDescription}
{
}

void DefaultDescription::print()
{
	std::cout << *_stringDescription << '\n';
}