#include "Collections.h"

template <typename Left, typename Right>
Pair<Left, Right>::Pair(Left left, Right right)
: _left{left}, _right{right}
{
}


template <typename Left, typename Right>
Left Pair<Left, Right>::left()
{
	return _left;
}

template <typename Left, typename Right>
Right Pair<Left, Right>::right()
{
	return _right;
}

template <typename Element>
Array<Element>::Array()
: _vector {new std::vector<Element>}
{
}

template <typename Element>
Array<Element>::Array(std::initializer_list<Element> initializer_list)
: Array()
{
	for (Element element : initializer_list) {
		_vector->push_back(element);
	}
}

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

template <typename Value, typename Key, typename AnyKey>
SharedPointer<Optional<Value>> value(SharedPointer<Map<Key, Value>> map, AnyKey key)
{
	SharedPointer<Array<Key>> mapKeys = map->keys();
	for (SharedPointer<Iterator<Key>> mapKeysIterator = mapKeys->iterator(); !mapKeysIterator->isDone(); mapKeysIterator->next()) {
		if (key == mapKeysIterator->current()) {
			return new Optional<Value>(map->value(mapKeysIterator->current())->value());
		}
	}
	return new Optional<Value>;
}

template <typename Key, typename Value>
StdAdapterMap<Key, Value>::StdAdapterMap()
: _map {new std::map<Key, Value>}, _keys {new Array<Key>()}
{
}

template <typename Key, typename Value>
SharedPointer<Optional<Value>> StdAdapterMap<Key, Value>::value(Key key)
{
	if (_map->count(key) != 0) {
		return new Optional<Value>(_map->at(key));
	}
	else {
		return new Optional<Value>;
	}
}

template <typename Key, typename Value>
void StdAdapterMap<Key, Value>::add(Key key, Value value)
{
	_map->insert(std::pair<Key, Value> {key, value});
}

template <typename Key, typename Value>
SharedPointer<Array<Key>> StdAdapterMap<Key, Value>::keys()
{
	return _keys;
}