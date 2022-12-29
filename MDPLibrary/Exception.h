#ifndef EXEPTION
#define EXEPTION

#include "Optional.h"
#include "SharedPointer.h"

class Traceback
{
	public:
	virtual void print() = 0;
	virtual ~Traceback() = default;
};

class DefaultTraceback : public Traceback
{
	public:
	DefaultTraceback(SharedPointer<std::string>);
	void print() override;

	private:
	SharedPointer<std::string> _stringTraceback;
};

class Description
{
	public:
	virtual void print() = 0;
	virtual ~Description() = default;
};

class DefaultDescription : public Description
{
	public:
	DefaultDescription(SharedPointer<std::string>);
	void print() override;

	private:
	SharedPointer<std::string> _stringDescription;
};

class Exception
{
	public:
	virtual void baseProcess() = 0;
	virtual SharedPointer<Traceback> traceback() = 0;
	virtual SharedPointer<Description> description() = 0;
	virtual SharedPointer<Optional<SharedPointer<Exception>>> lowerException() = 0;
	virtual ~Exception() = default;
};

class DefaultException : public Exception
{
	public:
	DefaultException(SharedPointer<Traceback>, SharedPointer<Description>, SharedPointer<Optional<SharedPointer<Exception>>>);
	DefaultException(SharedPointer<Traceback>, SharedPointer<Description>);
	void baseProcess() override;
	SharedPointer<Traceback> traceback() override;
	SharedPointer<Description> description() override;
	SharedPointer<Optional<SharedPointer<Exception>>> lowerException() override;

	private:
	SharedPointer<Traceback> _traceback;
	SharedPointer<Description> _description;
	SharedPointer<Optional<SharedPointer<Exception>>> _lowerException;
};

#include "Exception.cpp"

#endif