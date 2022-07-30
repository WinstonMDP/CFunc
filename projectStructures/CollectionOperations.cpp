#include "CollectionOperations.h"

template <template <typename> typename Collection, template <typename> typename Iterator, typename Element>
SharedPointer<Collection<Element>> subsegment(SharedPointer<Iterator<Element>> iterator, SharedPointer<Size> size)
{
	SharedPointer<Collection<Element>> outputCollection = new Collection<Element>;
	SharedPointer<Iterator<Element>> copiedIterator = iterator->copied();
	for (SharedPointer<Size> currentSize = new Size(0); *currentSize < *size; ++(*currentSize)) {
		outputCollection = outputCollection->collectionWithAddedElement(copiedIterator->currentElement());
		copiedIterator->next();
	}
	return outputCollection;
}

template <typename Element>
SharedPointer<Array<Element>> replacedArray(
	SharedPointer<Array<Element>> array,
	SharedPointer<Index> index,
	SharedPointer<Size> size,
	Element elementToPaste
)
{
	SharedPointer<Array<Element>> copiedArray = array->copied();
	for (long i = 0; i < *size; ++i) {
		copiedArray = copiedArray->arrayWithoutElement(index);
	}
	copiedArray = copiedArray->arrayWithAddedElement(index, elementToPaste);
	return copiedArray;
}