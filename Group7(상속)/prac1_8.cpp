#include <iostream>
using namespace std;

class Base
{
public:
    int fun()
    {
        cout << "Base::fun() called";
    }
    int fun(int i)
    {
        cout << "Base::fun(int i) called";
    }
};

class Derived : public Base
{
public:
    using Base::fun;
    // Base 클래스의 fun() 메서드 재정의
    // fun(int i) 메서드가 가려져 접근 불가
    int fun()
    {
        cout << "Derived::fun() called";
    }
};

int main()
{
    Derived d;
    d.fun(5);
    return 0;
}