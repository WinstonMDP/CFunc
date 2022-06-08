#ifndef COLLECTIONS
#define COLLECTIONS

#include "MDPLibrary/SharedPointer.h"
#include "MDPLibrary/Optional.h"
#include <map>
#include <vector>
#include <initializer_list>

template <typename Element>
class Iterator //iterator
{
	public:
    virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element current() = 0;
};

template <typename Left, typename Right>
class Pair
{
	public:
	Pair(Left, Right);
	Left left();
	Right right();

	private:
	Left _left;
	Right _right;
};

template <class Element>
class Array
{
	public:
	Array();
	Array(std::initializer_list<Element>);
	Element at(long);
	long size();
	void add(Element);
	SharedPointer<Iterator<Element>> iterator();

	private:
	SharedPointer<std::vector<Element>> _vector;
};

template <typename Element>
class ArrayIterator : public Iterator<Element>
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
	virtual SharedPointer<Optional<Value>> value(Key) = 0;
	virtual void add(Key, Value) = 0;
	virtual SharedPointer<Array<Key>> keys() = 0;
};

template <typename Value, typename Key, typename AnyKey>
SharedPointer<Optional<Value>> value(SharedPointer<Map<Key, Value>>, AnyKey);

template <typename Key, typename Value>
class StdAdapterMap
{
	public:
	StdAdapterMap();
	SharedPointer<Optional<Value>> value(Key) override;
	void add(Key, Value) override;
	SharedPointer<Array<Key>> keys() override;

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