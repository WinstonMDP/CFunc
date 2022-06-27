#ifndef SHARED_POINTER
#define SHARED_POINTER

#include <map>
#include <set>
#include <iostream>

class SharedPointerDestructor
{
	public:
	virtual ~SharedPointerDestructor() {std::cout << "Bey" << '\n';};
};

template <typename Type>
class SharedPointer
{
	public:
	SharedPointer(Type*);
	template <typename OtherType>
	SharedPointer(OtherType*)
	template <typename OtherType>
	SharedPointer(SharedPointer<OtherType>);
	SharedPointer(std::nullptr_t);
	SharedPointer();
	SharedPointer(const SharedPointer&);
	SharedPointer& operator=(const SharedPointer&);
	SharedPointer& operator=(const std::nullptr_t&);
	Type& operator*() const;
	Type* operator->();
	Type* primitivePointer() const;
	~SharedPointer();

	private:
	Type* _primitivePointer;
	static std::map<Type*, long long*> _primitivePointerToItsCountMap;
	static std::map<Type*, std::set<SharedPointerDestructor*>> _primitivePointerToOtherTypesSharedPointerDestructorsMap;
	long long* _primitivePointerCount;

    void deleteMethod();
};

template <typename Type>
bool operator==(const SharedPointer<Type>& a, const SharedPointer<Type>& b);
template <typename Type>
bool operator!=(const SharedPointer<Type>& a, const SharedPointer<Type>& b);

template <typename Type>
class DefaultSharedPointerDestructor : public SharedPointerDestructor
{
	public:
	DefaultSharedPointerDestructor(SharedPointer<Type>);
	~DefaultSharedPointerDestructor() override;

	private:
	SharedPointer<Type> _sharedPointer;
};

#include "SharedPointer.cpp"

#endif