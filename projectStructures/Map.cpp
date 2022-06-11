#include "Map.h"

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
void print(SharedPointer<Map<Key, Value>> map, long depth)
{
	SharedPointer<Iterator<Key>> mapKeysIterator = map->keys()->iterator();
	print("Map<Key, Value> {", depth);
	for (mapKeysIterator->first(); !mapKeysIterator->isDone(); mapKeysIterator->next()) {
		print(mapKeysIterator->current(), depth + 1);
		print(map->value(mapKeysIterator->current())->value(), depth + 1);
	}
	print("}", depth);
}

template <typename Key, typename Value>
DefaultMap<Key, Value>::DefaultMap()
: _map {new std::map<Key, Value>}, _keys {new DefaultArray<Key>}
{
}

template <typename Key, typename Value>
SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> DefaultMap<Key, Value>::iterator()
{

}

template <typename Key, typename Value>
SharedPointer<Collection<SharedPointer<Pair<Key, Value>>>> DefaultMap<Key, Value>::collectionWithAddedElement(SharedPointer<Pair<Key, Value>> mapPair)
{
	SharedPointer<std::map<Key, Value>> mapToAddElement = new std::map<Key, Value>(*_map);
	mapToAddElement->insert(std::pair<Key, Value> {mapPair->leftPart(), mapPair->rightPart()});
	return new DefaultMap<Key, Value>(mapToAddElement);
}

template <typename Key, typename Value>
long DefaultMap<Key, Value>::size()
{
	return _keys->size();
}

template <typename Key, typename Value>
SharedPointer<Optional<Value>> DefaultMap<Key, Value>::value(Key key)
{
	if (_map->count(key) == 0) {
		return new Optional<Value>;
	}
	else {
		return new Optional<Value>(_map->at(key));
	}
}

template <typename Key, typename Value>
SharedPointer<Array<Key>> DefaultMap<Key, Value>::keys()
{
	return _keys;
}

template <typename Key, typename Value>
MapIterator<Key, Value>::MapIterator(SharedPointer<Map<Key, Value>> map)
: MapIterator(map, map->keys()->iterator())
{
}

template <typename Key, typename Value>
void MapIterator<Key, Value>::first()
{
	_keysIterator->first();
}

template <typename Key, typename Value>
bool MapIterator<Key, Value>::isDone()
{
	return _keysIterator->isDone();
}

template <typename Key, typename Value>
void MapIterator<Key, Value>::next()
{
	_keysIterator->next();
}

template <typename Key, typename Value>
SharedPointer<Pair<Key, Value>> MapIterator<Key, Value>::current()
{
	Key currentKey = _keysIterator->current();
	return new DefaultPair<Key, Value>(currentKey, value(_map, currentKey)->value());
}

template <typename Key, typename Value>
MapIterator<Key, Value>::MapIterator(SharedPointer<Map<Key, Value>> map, SharedPointer<Iterator<Key>> keysIterator)
: _map {map}, _keysIterator {keysIterator}
{
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
OrderedByValueMap<Key, Value, OrderedCollection>::OrderedByValueMap()
: OrderedByValueMap(new OrderedCollection<SharedPointer<Pair<Key, Value>>>)
{
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> OrderedByValueMap<Key, Value, OrderedCollection>::iterator()
{
	return new MapIterator<Key, Value>(this);
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
SharedPointer<Collection<SharedPointer<Pair<Key, Value>>>> 
	OrderedByValueMap<Key, Value, OrderedCollection>::collectionWithAddedElement(SharedPointer<Pair<Key, Value>> mapPair)
{
	return new OrderedByValueMap<Key, Value, OrderedCollection>(_orderedCollection->collectionWithAddedElement<OrderedCollection>(mapPair));
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
long OrderedByValueMap<Key, Value, OrderedCollection>::size()
{
	return _orderedCollection->size();
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
SharedPointer<Optional<Value>> OrderedByValueMap<Key, Value, OrderedCollection>::value(Key key)
{
	SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> orderedCollectionIterator = _orderedCollection->iterator();
	for (orderedCollectionIterator->first(); !orderedCollectionIterator->isDone(); orderedCollectionIterator->next()) {
		if (orderedCollectionIterator->current()->leftElement() == key) {
			return new Optional<Value>(orderedCollectionIterator->current()->rightElement());
		}
	}
	return new Optional<Value>;
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
SharedPointer<Array<Key>> OrderedByValueMap<Key, Value, OrderedCollection>::keys()
{
	SharedPointer<DefaultArray<Key>> keysArray = new DefaultArray<Key>;
	SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> orderedCollectionIterator = _orderedCollection->iterator();
	for (orderedCollectionIterator->first(); !orderedCollectionIterator->isDone(); orderedCollectionIterator->next()) {
		keysArray = (*keysArray).collectionWithAddedElement<DefaultArray>(orderedCollectionIterator->current()->leftElement());
	}
	return keysArray;
}

template <typename Key, typename Value, template <typename> typename OrderedCollection>
OrderedByValueMap<Key, Value, OrderedCollection>::OrderedByValueMap(SharedPointer<OrderedCollection<SharedPointer<Pair<Key, Value>>>> orderedCollection)
: _orderedCollection {orderedCollection}
{
}