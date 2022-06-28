#ifndef STRUCTURES
#define STRUCTURES

#include "SharedPointer.h"

template <typename Element>
class Iterator
{
	public:
    virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element currentElement() = 0;
	virtual ~Iterator() = default;
};

template <typename Element>
class Collection
{
	public:
	virtual Iterator<Element>* iterator() = 0;
	virtual Collection<Element>* collectionWithAddedElement(Element) = 0;
	virtual long size() = 0;
	virtual ~Collection() = default;
};

template <typename LeftElement, typename RightElement>
class Pair
{
	public:
	virtual LeftElement leftElement() = 0;
	virtual RightElement rightElement() = 0;
	virtual ~Pair() = default;
};

template <typename LeftElement, typename RightElement>
class DefaultPair : public Pair<LeftElement, RightElement>
{
	public:
	DefaultPair(LeftElement, RightElement);
	LeftElement leftElement() override;
	RightElement rightElement() override;

	private:
	LeftElement _leftElement;
	RightElement _rightElement;
};

#include "Structures.cpp"

#endif