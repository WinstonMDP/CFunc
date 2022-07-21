#include "CollectionOperations.h"

template <template <typename> typename Collection, typename Element>
SharedPointer<Collection<Element>> subsegment(SharedPointer<Iterator<Element>> iterator, Size size)
{
	SharedPointer<Collection<Element>> outputCollection = new Collection<Element>;
	Iterator<Element> copiedIterator = *iterator;
	for (SharedPointer<Size> currentSize = new long(0); currentSize < size; ++currentSize) {
		outputCollection = outputCollection->collectionWithAddedElement(iterator.currentElement());
		iterator.next();
	}
	return outputCollection;
}

template <typename Element>
SharedPointer<Collection<Element>> replacedCollection(
	SharedPointer<Array<Element>> array,
	SharedPointer<Index> index,
	SharedPointer<Size> size,
	SharedPointer<Element> elementToPaste
)
{
	SharedPointer<Array<Element>> copiedArray = new Array<Element>(array);
	for (long i = 0; i < size; ++i) {
		copiedArray = copiedArray->arrayWithoutElement(index);
	}
	copiedArray = copiedArray->arrayWithAddedElement(index, element);
	return copiedArray;
}