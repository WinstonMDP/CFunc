#include "Array.h"

#include "../Printer.h"

#include "../MDPLibrary/Exception.h"

Index::Index(long longNumber)
: _longNumber {longNumber}
{
	isNonnegativeNumberValidate(longNumber);
}

Index::operator long&()
{
	return _longNumber;
}
template <typename AElement, typename BElement>
bool operator==(SharedPointer<Array<AElement>> aArray, SharedPointer<Array<BElement>> bArray)
{
	SharedPointer<Iterator<AElement>> aIterator = aArray->iterator();
	SharedPointer<Iterator<BElement>> bIterator = bArray->iterator();
	for (aIterator->first(), bIterator->first(); !aIterator->isDone() && !bIterator->isDone(); aIterator->next(), bIterator->next()) {
		if (aIterator->currentElement() != bIterator->currentElement()) {
			return false;
		}
	}
	return true;
}

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
DefaultArray<Element>* DefaultArray<Element>::arrayWithAddedElement(SharedPointer<Index> index, Element element)
{
	SharedPointer<std::vector<Element>> vectorToAddElement = new std::vector<Element>(*_vector);
	vectorToAddElement->insert(vectorToAddElement->begin() + *index, element);
	return new DefaultArray<Element>(vectorToAddElement);
}

template <typename Element>
DefaultArray<Element>* DefaultArray<Element>::arrayWithoutElement(SharedPointer<Index> index)
{
	SharedPointer<std::vector<Element>> vectorToRemoveElement = new std::vector<Element>(*_vector);
	vectorToRemoveElement->erase(vectorToRemoveElement->begin() + *index);
	return new DefaultArray<Element>(vectorToRemoveElement);
}

template <typename Element>
SharedPointer<Size> DefaultArray<Element>::size()
{
	return new Size(_vector->size());
}

template <typename Element>
Element DefaultArray<Element>::element(SharedPointer<Index> index)
{
	if (*index > *size()) {
		throw SharedPointer<Exception>(new DefaultException(
			new DefaultTraceback(new std::string("template <typename Element>\nElement DefaultArray<Element>::element(long index)")),
			new DefaultDescription(new std::string("Argument index larger than the size"))
		));
	}
	return _vector->at(*index);
}

template <typename Element>
DefaultArray<Element>* DefaultArray<Element>::copied()
{
	SharedPointer<std::vector<Element>> copiedVector = new std::vector<Element>(*_vector);
	return new DefaultArray<Element>(copiedVector);
}

template <typename Element>
ArrayIterator<Element>::ArrayIterator(SharedPointer<Array<Element>> array)
: _array {array}, _currentIndex {new Index(0)}
{
}

template <typename Element>
void ArrayIterator<Element>::first()
{
	*_currentIndex = 0;
}

template <typename Element>
bool ArrayIterator<Element>::isDone()
{
	return *_array->size() == *_currentIndex;
}

template <typename Element>
Element ArrayIterator<Element>::currentElement()
{
	return _array->element(_currentIndex);
}

template <typename Element>
void ArrayIterator<Element>::next()
{
	++(*_currentIndex);
}

template <typename Element>
ArrayIterator<Element>* ArrayIterator<Element>::copied()
{
	return new ArrayIterator<Element>(_array->copied());
}