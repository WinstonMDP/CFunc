#include "Collections.h"
#include <map>
#include <vector>

template <typename Element>
Element Array<Element>::at(long index)
{
	return _vector->at(index);
}

template <typename Element>
long Array<Element>::size()
{
	return _vector->size();
}

template <typename Element>
void Array<Element>::add(Element element)
{
	_vector->push_back(element);
}

template <typename Element>
SharedPointer<Iterator<Element>> Array<Element>::iterator()
{
	return new ArrayIterator<Element>(this);
}

template <typename Element>
ArrayIterator<Element>::ArrayIterator(SharedPointer<Array<Element>> array)
: _array {array}, _currentIndex {0}
{
}

template <typename Element>
void ArrayIterator<Element>::first()
{
	_currentIndex = 0;
}

template <typename Element>
bool ArrayIterator<Element>::isDone()
{
	return _array->size() == _currentIndex;
}

template <typename Element>
Element ArrayIterator<Element>::current()
{
	return _array->at(_currentIndex);
}

template <typename Element>
void ArrayIterator<Element>::next()
{
	++_currentIndex;
}

template <typename Key, typename Value>
SharedPointer<Optional<Value>> Map<Key, Value>::value(Key key)
{
	if (_map->count(key) != 0) {
		return new Optional<Value>(_map->at(key));
	}
	else {
		return new Optional<Value>(nullptr);
	}
}

template <typename Key, typename Value>
template <typename OtherKey>
SharedPointer<Optional<Value>> Map<Key, Value>::value(OtherKey key)
{
	SharedPointer<Array<Key>> mapKeys = keys();
	for (SharedPointer<Iterator<Key>> mapKeysIterator = mapKeys->iterator(); !mapKeysIterator->isDone(); mapKeysIterator->next()) {
		if (key == mapKeysIterator->current()) {
			return new Optional<Value>(value(mapKeysIterator->current())->value());
		}
	}
	return new Optional<Value>(nullptr);
}

template <typename Key, typename Value>
void Map<Key, Value>::add(Key key, Value value)
{
	_map.at(key) = value;
}

template <typename Key, typename Value>
void Map<Key, Value>::removeElement(Key key)
{
	_map.erase(key);
}

template <typename Key, typename Value>
SharedPointer<Array<Key>> Map<Key, Value>::keys()
{
	return _keys;
}