#ifndef EXEPTION
#define EXEPTION

#include "Optional.h"
#include "SharedPointer.h"

class Traceback
{
	public:
	virtual void print() = 0;
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
};

class DefaultDescription : public Description
{
	public:
	DefaultDescription(SharedPointer<std::string>);
	void print() override;

	private:
	SharedPointer<std::string> _stringDescription;
};

class Exeption
{
	public:
	virtual void baseProcess() = 0;
	virtual SharedPointer<Traceback> traceback() = 0;
	virtual SharedPointer<Description> description() = 0;
	virtual SharedPointer<Optional<SharedPointer<Exeption>>> lowerExeption() = 0;
};

class DefaultExeption : public Exeption
{
	public:
	DefaultExeption(SharedPointer<Traceback>, SharedPointer<Description>, SharedPointer<Optional<SharedPointer<Exeption>>>);
	DefaultExeption(SharedPointer<Traceback>, SharedPointer<Description>);
	void baseProcess() override;
	SharedPointer<Traceback> traceback() override;
	SharedPointer<Description> description() override;
	SharedPointer<Optional<SharedPointer<Exeption>>> lowerExeption() override;

	private:
	SharedPointer<Traceback> _traceback;
	SharedPointer<Description> _description;
	SharedPointer<Optional<SharedPointer<Exeption>>> _lowerExeption;
};

#include "Exeption.cpp"

#endif