#include <iostream>
using namespace std;

class Base
{
public:
    ~Base()
    {
        cout << " Base destructor" << endl;
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        cout << " Derived destructor" << endl;
    }
};

int main()
{
    Derived d;
    return 0;
}

// 소멸자 호출 순서
// Derived 객체 d 소멸될 때 Derived 클래스 소멸자가 먼저 호출
// 그 다음 Base 클래스의 소멸자가 호출