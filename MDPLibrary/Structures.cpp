#include "Structures.h"

#include "Exeption.h"

void isNonnegativeNumberValidate(long number)
{
	if (number < 0) {
		throw SharedPointer<Exeption>(new DefaultExeption(
			new DefaultTraceback(new std::string("void isNonnegativeNumberValidate(long number)")),
			new DefaultDescription(new std::string("number mast be >= 0"))
		));
	}
}

Size::Size(long longNumber)
: _longNumber {longNumber}
{
	isNonnegativeNumberValidate(longNumber);
}

Size::operator long&()
{
	return _longNumber;
}

template <typename AElement, typename BElement>
bool operator==(SharedPointer<Collection<AElement>> aCollection, SharedPointer<Collection<BElement>> bCollection)
{
	SharedPointer<Iterator<AElement>> aIterator = aCollection->iterator();
	SharedPointer<Iterator<BElement>> bIterator = bCollection->iterator();
	for (aIterator->first(), bIterator->first(); !aIterator->isDone() && !bIterator->isDone(); aIterator->next(), bIterator->next()) {
		if (aIterator->currentElement() != bIterator->currentElement()) {
			return false;
		}
	}
	return true;
}

template <typename LeftElement, typename RightElement>
DefaultPair<LeftElement, RightElement>::DefaultPair(LeftElement leftElement, RightElement rightElement)
: _leftElement {leftElement}, _rightElement {rightElement}
{
}

template <typename LeftElement, typename RightElement>
LeftElement DefaultPair<LeftElement, RightElement>::leftElement()
{
	return _leftElement;
}

template <typename LeftElement, typename RightElement>
RightElement DefaultPair<LeftElement, RightElement>::rightElement()
{
	return _rightElement;
}