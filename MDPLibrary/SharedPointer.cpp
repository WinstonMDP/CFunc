#include "SharedPointer.h"

template <typename Type>
SharedPointer<Type>::SharedPointer(Type* primitivePointer)
: SharedPointer(primitivePointer, primitivePointerCount(primitivePointer))
{
}

template <typename Type>
template <typename OtherType>
SharedPointer<Type>::SharedPointer(SharedPointer<OtherType> otherTypeSharedPointer)
: SharedPointer(otherTypeSharedPointer.primitivePointer(), otherTypeSharedPointer.primitivePointerCount())
{
}

template <typename Type>
SharedPointer<Type>::SharedPointer(std::nullptr_t)
: SharedPointer(nullptr, nullptr)
{
}

template <typename Type>
SharedPointer<Type>::SharedPointer()
: SharedPointer(nullptr)
{
}

template <typename Type>
SharedPointer<Type>::SharedPointer(const SharedPointer<Type>& sharedPointer)
: SharedPointer(sharedPointer.primitivePointer(), sharedPointer.primitivePointerCount())
{
}

template <typename Type>
SharedPointer<Type>& SharedPointer<Type>::operator=(const SharedPointer<Type>& sharedPointer)
{
    deleteMethod();
    _primitivePointer = sharedPointer.primitivePointer();
    if (_primitivePointer != nullptr) {
        _primitivePointerCount = primitivePointerToItsCountMap.at(_primitivePointer);
        ++(*_primitivePointerCount);
    }
    else {
        _primitivePointerCount = nullptr;
    }
    return *this;
}

template <typename Type>
SharedPointer<Type>& SharedPointer<Type>::operator=(const std::nullptr_t& sharedPointer)
{
    throw "template <typename Type>:\n\
SharedPointer<Type>& SharedPointer<Type>::operator=(const std::nullptr_t& sharedPointer)\nGet out with your nullptr.";
}

template <typename Type>
Type& SharedPointer<Type>::operator*() const
{
    return *_primitivePointer;
}

template <typename Type>
Type* SharedPointer<Type>::operator->()
{
    return _primitivePointer;
}

template <typename Type>
Type* SharedPointer<Type>::primitivePointer() const
{
    return _primitivePointer;
}

template <typename Type>
long* SharedPointer<Type>::primitivePointerCount() const
{
    return _primitivePointerCount;
}

template <typename Type>
SharedPointer<Type>::~SharedPointer()
{
    deleteMethod();
}

template <typename Type>
SharedPointer<Type>::SharedPointer(Type* primitivePointer, long* primitivePointerCount)
: _primitivePointer {primitivePointer}, _primitivePointerCount {incrementedPrimitivePointerCount(primitivePointerCount)}
{
}

template <typename Type>
long* SharedPointer<Type>::primitivePointerCount(Type* primitivePointer)
{
    long* primitivePointerCount;
    if (primitivePointerToItsCountMap.count(primitivePointer) == 0) {
        primitivePointerCount = new long(0);
        primitivePointerToItsCountMap.insert(std::pair<void*, long*>(primitivePointer, primitivePointerCount));
    }
    else {
        primitivePointerCount = primitivePointerToItsCountMap.at(static_cast<void*>(primitivePointer));
    }
    return primitivePointerCount;
}

template <typename Type>
long* SharedPointer<Type>::incrementedPrimitivePointerCount(long* primitivePointerCount)
{
    if (primitivePointerCount != nullptr) {
        ++(*primitivePointerCount);
    }
    return primitivePointerCount;
}

template <typename Type>
void SharedPointer<Type>::deleteMethod()
{
    if (_primitivePointer != nullptr) {
        --(*_primitivePointerCount);
        if (*_primitivePointerCount == 0) {
            primitivePointerToItsCountMap.erase(_primitivePointer);
            delete _primitivePointer;
            delete _primitivePointerCount;
        }
    }
}

bool operator==(SharedPointer<std::string> a, SharedPointer<std::string> b)
{
    return *a == *b;
}

bool operator==(SharedPointer<long> a, SharedPointer<long> b)
{
    return *a == *b;
}

bool operator<(SharedPointer<std::string> a, SharedPointer<std::string> b)
{
    return *a < *b;
}

bool operator<(SharedPointer<long> a, SharedPointer<long> b)
{
    return *a < *b;
}