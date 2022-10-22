#include "Exception.h"

#include <iostream>

DefaultException::DefaultException(
	SharedPointer<Traceback> traceback,
	SharedPointer<Description> description,
	SharedPointer<Optional<SharedPointer<Exception>>> lowerException
)
: _traceback {traceback}, _description {description}, _lowerException {lowerException}
{
}

DefaultException::DefaultException(SharedPointer<Traceback> traceback, SharedPointer<Description> description)
: DefaultException(traceback, description, new Optional<SharedPointer<Exception>>)
{
}

void DefaultException::baseProcess()
{
	_traceback->print();
	_description->print();
}

SharedPointer<Traceback> DefaultException::traceback()
{
	return _traceback;
}

SharedPointer<Description> DefaultException::description()
{
	return _description;
}

SharedPointer<Optional<SharedPointer<Exception>>> DefaultException::lowerException()
{
	return _lowerException;
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