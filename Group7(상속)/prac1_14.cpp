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
    // 선언만 하고 초기화 안 함 -> 런타임 오류
    // A *a;
    A *a = new A();
    a->func();

    delete a;
    return 0;
}