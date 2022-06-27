#include "SharedPointer.h"

#include <iostream>

template <typename Type>
SharedPointer<Type>::SharedPointer(Type* primitivePointer)
: _primitivePointer {primitivePointer}
{
    if (_primitivePointerToItsCountMap.count(_primitivePointer) == 0) {
        long long* newPrimitivePointerCount = new long long(1);
        _primitivePointerToItsCountMap.insert(std::pair<Type*, long long*>(_primitivePointer, newPrimitivePointerCount));
        _primitivePointerCount = newPrimitivePointerCount;
    }
    else {
        _primitivePointerCount = _primitivePointerToItsCountMap.at(_primitivePointer);
        ++(*_primitivePointerCount);
    }
}

template <typename Type>
template <typename OtherType>
SharedPointer<Type>::SharedPointer(OtherType* otherTypePrimitivePointer)
: SharedPointer(SharedPointer<Type>(otherTypePrimitivePointer))
{
}

template <typename Type>
template <typename OtherType>
SharedPointer<Type>::SharedPointer(SharedPointer<OtherType> otherValueSharedPointer)
: SharedPointer(otherValueSharedPointer.primitivePointer())
{
    if (_primitivePointerToOtherTypesSharedPointerDestructorsMap.count(otherValueSharedPointer.primitivePointer()) == 0) {
        _primitivePointerToOtherTypesSharedPointerDestructorsMap.insert(
            std::pair<OtherType*, std::set<SharedPointerDestructor*>>(otherValueSharedPointer.primitivePointer(), std::set<SharedPointerDestructor*>())
        );
    }
    _primitivePointerToOtherTypesSharedPointerDestructorsMap.at(otherValueSharedPointer.primitivePointer()).insert(
        new DefaultSharedPointerDestructor<OtherType>(otherValueSharedPointer)
    );
}

template <typename Type>
SharedPointer<Type>::SharedPointer(std::nullptr_t primitivePointer)
: _primitivePointer {primitivePointer}
{
    _primitivePointerCount = nullptr;
}

template <typename Type>
SharedPointer<Type>::SharedPointer()
: SharedPointer(nullptr)
{
}

template <typename Type>
SharedPointer<Type>::SharedPointer(const SharedPointer<Type>& sharedPointer)
: SharedPointer(sharedPointer.primitivePointer())
{
}

template <typename Type>
SharedPointer<Type>& SharedPointer<Type>::operator=(const SharedPointer<Type>& sharedPointer)
{
    deleteMethod();
    _primitivePointer = sharedPointer.primitivePointer();
    if (_primitivePointer != nullptr) {
        _primitivePointerCount = _primitivePointerToItsCountMap.at(_primitivePointer);
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
bool operator==(const SharedPointer<Type>& a, const SharedPointer<Type>& b)
{
    return a.primitivePointer() == b.primitivePointer();
}

template <typename Type>
bool operator!=(const SharedPointer<Type>& a, const SharedPointer<Type>& b)
{
    return a.primitivePointer() != b.primitivePointer();
}

template <typename Type>
Type* SharedPointer<Type>::primitivePointer() const
{
    return _primitivePointer;
}

template <typename Type>
SharedPointer<Type>::~SharedPointer()
{
    deleteMethod();
}

template <typename Type>
void SharedPointer<Type>::deleteMethod()
{
    if (_primitivePointer != nullptr) {
        --(*_primitivePointerCount);
        if (*_primitivePointerCount == 0) {
            _primitivePointerToItsCountMap.erase(_primitivePointer);
            if (_primitivePointerToOtherTypesSharedPointerDestructorsMap.count(_primitivePointer) != 0) {
                std::cout << "Vot tak" << '\n';
                _primitivePointerToOtherTypesSharedPointerDestructorsMap.at(_primitivePointer).clear();
                _primitivePointerToOtherTypesSharedPointerDestructorsMap.erase(_primitivePointer);
            }
            delete _primitivePointer;
            delete _primitivePointerCount;
        }
    }
}

template <typename Type>
std::map<Type*, long long*> SharedPointer<Type>::_primitivePointerToItsCountMap;

template <typename Type>
std::map<Type*, std::set<SharedPointerDestructor*>> SharedPointer<Type>::_primitivePointerToOtherTypesSharedPointerDestructorsMap;

template <typename Type>
DefaultSharedPointerDestructor<Type>::DefaultSharedPointerDestructor(SharedPointer<Type> sharedPointer)
: _sharedPointer {sharedPointer}
{
}

template <typename Type>
DefaultSharedPointerDestructor<Type>::~DefaultSharedPointerDestructor()
{
    std::cout << "Hey" << '\n';
}