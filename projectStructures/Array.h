#ifndef ARRAY
#define ARRAY

#include <initializer_list>
#include <vector>

#include "../MDPLibrary/SharedPointer.h"
#include "../MDPLibrary/Structures.h"

template <typename Element>
class Array : public Collection<Element>
{
	public:
	virtual Element elementAtIndex(long) = 0;
	virtual SharedPointer<Array<Element>> arrayWithoutElementAtIndex(long) = 0;
};

template <typename Element>
void print(SharedPointer<Array<Element>>, long depth = 0);

template <typename Element>
class DefaultArray : public Array<Element>
{
	public:
	DefaultArray(SharedPointer<std::vector<Element>>);
	DefaultArray();
	DefaultArray(std::initializer_list<Element>);

	SharedPointer<Iterator<Element>> iterator() override;

	SharedPointer<Collection<Element>> collectionWithAddedElement(Element) override;
	template <template <typename> typename BaseClass>
	SharedPointer<BaseClass<Element>> collectionWithAddedElement(Element);

	SharedPointer<Array<Element>> arrayWithoutElementAtIndex(long) override;
	template <template <typename> typename BaseClass>
	SharedPointer<BaseClass<Element>> arrayWithoutElementAtIndex(long);

	long size() override;
	Element elementAtIndex(long) override;

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

#include "Array.cpp"

#endif