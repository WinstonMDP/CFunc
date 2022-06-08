#ifndef OPTIONAL
#define OPTIONAL

template <typename Value>
class Optional
{
	public:
	Optional(Value);
	Optional();
	Optional(std::nullptr_t);
	bool doesValueExist();
	Value value();

	private:
	Optional(Value, bool);

	Value _value;
	bool _doesValueExist;
};

#include "Optional.cpp"

#endif