#ifndef COLLECTIONS
#define COLLECTIONS

#include "MDPLibrary/SharedPointer.h"
#include "MDPLibrary/Optional.h"
#include <map>
#include <vector>

template <typename Element>
class Iterator //iterator
{
	public:
    virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element current() = 0;
};

template <class Element>
class Array
{
	public:
	Element at(long);
	long size();
	void add(Element);
	SharedPointer<Iterator<Element>> iterator();

	private:
	SharedPointer<std::vector<Element>> _vector;
};

template <typename Element>
class ArrayIterator : public Iterator <Element>
{
	public:
	ArrayIterator(SharedPointer<Array<Element>>);
	void first() override;
	bool isDone() override;
	Element current() override;
	void next() override;

	private:
	SharedPointer<Array<Element>> _array;
	long _currentIndex;
};

template <typename Key, typename Value>
class Map
{
	public:
	SharedPointer<Optional<Value>> value(Key);
	template <typename OtherKey>
	SharedPointer<Optional<Value>> value(OtherKey);
	void add(Key, Value);
	void removeElement(Key);
	SharedPointer<Array<Key>> keys();

	private:
	SharedPointer<std::map<Key, Value>> _map;
	SharedPointer<Array<Key>> _keys;
};

template <typename Element>
class Set
{
	public:
	void add(Element);
	void removeElement(Element);
};

#include "Collections.cpp"

#endif