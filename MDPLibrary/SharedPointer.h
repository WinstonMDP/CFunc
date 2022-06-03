#ifndef SHARED_POINTER
#define SHARED_POINTER

#include <map>

template <typename Value>
class SharedPointer
{
	public:
	SharedPointer(Value*);
	SharedPointer(std::nullptr_t);
	SharedPointer();
	SharedPointer(const SharedPointer&);
	SharedPointer& operator=(const SharedPointer&);
	Value& operator*() const;
	Value* operator->();
	Value* primitivePointer() const;
	~SharedPointer();
	

	private:
	Value* _primitivePointer;
	static std::map<Value*, long long*> _primitivePointersCounts;
	long long* _primitivePointerCount;

    void deleteMethod();
};

template <typename Value>
bool operator==(const SharedPointer<Value>& a, const SharedPointer<Value>& b);
template <typename Value>
bool operator!=(const SharedPointer<Value>& a, const SharedPointer<Value>& b);

#include "SharedPointer.cpp"

#endif