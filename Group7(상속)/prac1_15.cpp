#include <iostream>
using namespace std;

class A
{
    double d;

public:
    virtual void func()
    {
        cout << "In class A\n";
    }
};

class B : public A
{
    int a = 15;

public:
    void func() override
    {
        cout << "In class B\n";
    }
};

int main()
{
    A *a = new A();
    B b;
    a = &b;
    a->func();
    return 0;
}