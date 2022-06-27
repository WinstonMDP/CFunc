#include <iostream>

class B
{
    public:
    B(char ch)
    : _ch {ch}
    {
    }

    char come()
    {
        return _ch;
    }

    private:
    char _ch;
};

int main()
{
    void* a = new B('1');
    B* b = static_cast<B*>(a);
    std::cout << b->come();
}