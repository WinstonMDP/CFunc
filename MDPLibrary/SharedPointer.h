#ifndef SHARED_POINTER
#define SHARED_POINTER

#include <map>
#include <set>

std::map<void*, long*> primitivePointerToItsCountMap;

template <typename Type>
class SharedPointer
{
	public:
	SharedPointer(Type*);
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
	long* primitivePointerCount() const;
	~SharedPointer();

	private:
	SharedPointer(Type*, long*);
	long* primitivePointerCount(Type*);
	long* incrementedPrimitivePointerCount(long*);
    void deleteMethod();

	Type* _primitivePointer;
	long* _primitivePointerCount;
};

bool operator==(SharedPointer<std::string>, SharedPointer<std::string>);
bool operator==(SharedPointer<std::string>, std::string);
bool operator==(SharedPointer<long>, SharedPointer<long>);
bool operator==(SharedPointer<long>, long);
bool operator<(SharedPointer<std::string>, SharedPointer<std::string>);
bool operator<(SharedPointer<long>, SharedPointer<long>);

#include "SharedPointer.cpp"

#endif