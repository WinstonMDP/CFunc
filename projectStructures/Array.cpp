#include "Array.h"

#include "../Printer.h"

#include "../MDPLibrary/Exeption.h"

template <typename Element>
void print(SharedPointer<Array<Element>> array, long depth)
{
	print("Array<Element> {", depth);
	SharedPointer<Iterator<Element>> arrayIterator = array->iterator();
	for (arrayIterator->first(); !arrayIterator->isDone(); arrayIterator->next()) {
		print(arrayIterator->currentElement(), depth + 1);
	}
	print("}", depth);
}

template <typename Element>
DefaultArray<Element>::DefaultArray(SharedPointer<std::vector<Element>> vector)
: _vector {vector}
{
}

template <typename Element>
DefaultArray<Element>::DefaultArray()
: DefaultArray(new std::vector<Element>)
{
}

template <typename Element>
DefaultArray<Element>::DefaultArray(std::initializer_list<Element> initializer_list)
: DefaultArray()
{
	for (Element element : initializer_list) {
		_vector->push_back(element);
	}
}

template <typename Element>
Iterator<Element>* DefaultArray<Element>::iterator()
{
	return new ArrayIterator<Element>(this);
}

template <typename Element>
DefaultArray<Element>* DefaultArray<Element>::collectionWithAddedElement(Element element)
{
	SharedPointer<std::vector<Element>> vectorToAddElement = new std::vector<Element>(*_vector);
	vectorToAddElement->push_back(element);
	return new DefaultArray<Element>(vectorToAddElement);
}

template <typename Element>
DefaultArray<Element>* DefaultArray<Element>::arrayWithoutElementAtIndex(long index)
{
	SharedPointer<std::vector<Element>> vectorToRemoveElement = new std::vector<Element>(*_vector);
	vectorToRemoveElement->erase(vectorToRemoveElement->begin() + index);
	return new DefaultArray<Element>(vectorToRemoveElement);
}

template <typename Element>
long DefaultArray<Element>::size()
{
	return _vector->size();
}

template <typename Element>
Element DefaultArray<Element>::elementAtIndex(long index)
{
	if (index > size()) {
		throw SharedPointer<Exeption>(new DefaultExeption(
			new DefaultTraceback(new std::string("template <typename Element>\nElement DefaultArray<Element>::elementAtIndex(long index)")),
			new DefaultDescription(new std::string("Argument index larger than the size"))
		));
	}
	return _vector->at(index);
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
Element ArrayIterator<Element>::currentElement()
{
	return _array->elementAtIndex(_currentIndex);
}

template <typename Element>
void ArrayIterator<Element>::next()
{
	++_currentIndex;
}