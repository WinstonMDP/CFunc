#ifndef ARRAY
#define ARRAY

#include <initializer_list>
#include <vector>

#include "../MDPLibrary/SharedPointer.h"
#include "../MDPLibrary/Structures.h"

class Index
{
	public:
	Index(long);
	operator long&();

	private:
	long _longNumber;
};

template <typename Element>
class Array : public Collection<Element>
{
	public:
	virtual Array<Element>* collectionWithAddedElement(Element) = 0;
	virtual Element element(SharedPointer<Index>) = 0;
	virtual Array<Element>* arrayWithoutElement(SharedPointer<Index>) = 0;
	virtual ~Array() = default; 
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
	Iterator<Element>* iterator() override;
	DefaultArray<Element>* collectionWithAddedElement(Element) override;
	DefaultArray<Element>* arrayWithoutElement(SharedPointer<Index>) override;
	SharedPointer<Size> size() override;
	Element element(SharedPointer<Index>) override;

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
	Element currentElement() override;
	void next() override;

	private:
	SharedPointer<Array<Element>> _array;
	SharedPointer<Index> _currentIndex;
};

#include "Array.cpp"

#endif