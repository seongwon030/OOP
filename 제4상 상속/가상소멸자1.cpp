#include <iostream>
using namespace std;

class Base
{
public:
    Base() { cout << "Constructing base\n"; }
    virtual ~Base() { cout << "Destructing base\n"; }
    // 소멸자가 가상함수로 선언되지 않았다면 Derived 클래스 소멸자가 호출되지 않을 수 있음
};

class Derived : public Base
{
    int y;

public:
    Derived() { cout << "Constructing derived\n"; }
    ~Derived() { cout << "Destructing derived\n"; }
};

int main()
{
    Derived *d = new Derived(); // Derived 객체 생성
    Base *b = d;                // Base 포인터 b가 Derived 객체 가리킴
    delete b;

    return 0;
}