#ifndef MAP
#define MAP

#include <map>

#include "../MDPLibrary/Optional.h"
#include "../MDPLibrary/SharedPointer.h"
#include "../MDPLibrary/Structures.h"

template <typename Key, typename Value>
class Map : public Collection<SharedPointer<Pair<Key, Value>>>
{
	public:
	virtual SharedPointer<Optional<Value>> value(Key) = 0;
	virtual SharedPointer<Array<Key>> keys() = 0;
};

template <typename Value, typename Key, typename AnyKey>
SharedPointer<Optional<Value>> value(SharedPointer<Map<Key, Value>>, AnyKey);

template <typename Key, typename Value>
void print(SharedPointer<Map<Key, Value>>, long depth = 0);

template <typename Key, typename Value>
class DefaultMap : public Map<Key, Value>
{
	public:
	DefaultMap();
	SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> iterator() override;

	SharedPointer<Collection<SharedPointer<Pair<Key, Value>>>> collectionWithAddedElement(SharedPointer<Pair<Key, Value>>) override;
	template <template <typename> typename BaseClass>
	SharedPointer<BaseClass<SharedPointer<Pair<Key, Value>>>> collectionWithAddedElement(SharedPointer<Pair<Key, Value>>);

	long size() override;
	SharedPointer<Optional<Value>> value(Key) override;
	SharedPointer<Array<Key>> keys() override;

	private:
	SharedPointer<std::map<Key, Value>> _map;
	SharedPointer<Array<Key>> _keys;
};

template <typename Key, typename Value>
class MapIterator : public Iterator<SharedPointer<Pair<Key, Value>>>
{
	public:
	MapIterator(SharedPointer<Map<Key, Value>>);
	void first() override;
	bool isDone() override;
	SharedPointer<Pair<Key, Value>> current() override;
	void next() override;

	private:
	MapIterator(SharedPointer<Map<Key, Value>>, SharedPointer<Iterator<Key>>);

	SharedPointer<Map<Key, Value>> _map;
	SharedPointer<Iterator<Key>> _keysIterator;
};

template <typename Key, typename Value, template <typename> typename OrderedCollection = DefaultArray>
class OrderedByValueMap : public Map<Key, Value>
{
	public:
	OrderedByValueMap();
	SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> iterator() override;


	SharedPointer<Collection<SharedPointer<Pair<Key, Value>>>> collectionWithAddedElement(SharedPointer<Pair<Key, Value>>) override;
	SharedPointer<OrderedByValueMap<Key, Value>> collectionWithAddedElement(SharedPointer<Pair<Key, Value>>);

	long size() override;
	SharedPointer<Optional<Value>> value(Key) override;
	SharedPointer<Array<Key>> keys() override;

	private:
	OrderedByValueMap(SharedPointer<OrderedCollection<SharedPointer<Pair<Key, Value>>>>);

	SharedPointer<OrderedCollection<SharedPointer<Pair<Key, Value>>>> _orderedCollection;
};

#include "Map.cpp"

#endif