#include "Optional.h"

template <typename Value>
Optional<Value>::Optional(Value value)
: Optional(value, true)
{
}

template <typename Value>
Optional<Value>::Optional() // bad
: _doesValueExist {false}
{
}

template <typename Value>
Optional<Value>::Optional(std::nullptr_t)
{
	throw "template <typename value> Optional<value>::Optional(std::nullptr_t):\nGet out with your nullptr.";
}

template <typename Value>
bool Optional<Value>::doesValueExist()
{
	return _doesValueExist;
}

template <typename Value>
Value Optional<Value>::value()
{
	if (!doesValueExist()) {
		throw "template <typename Value>\nValue Optional<Value>::value():\nValue does not exist.";
	}
	return _value;
}

template <typename Value>
Optional<Value>::Optional(Value value, bool doesValueExist)
: _value {value}, _doesValueExist {doesValueExist}
{
}