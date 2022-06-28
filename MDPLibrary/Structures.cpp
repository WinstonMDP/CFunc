#include "Structures.h"

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