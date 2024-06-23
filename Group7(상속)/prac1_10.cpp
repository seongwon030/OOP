#include <iostream>
using namespace std;

class Base
{
public:
    virtual string print() const
    {
        return "This is Base class";
    }
};

class Derived : public Base
{
public:
    virtual string print() const
    {
        return "This is Derived class";
    }
};

// void describe(Base p)
void describe(Base &p)
// Base 객체에 대한 상수 참조를 받음
{
    // Base 타입의 객체를 값으로 받음
    // Derived 객체 d를 describe에 전달할 때 객체 슬라이싱 발생
    // Derived 객체의 Base 부분만 복사되어 전달, 실제로는 Base 객체로 다루어짐
    // Derived가 아닌 Base의 print 메서드 호출
    cout << p.print() << endl;
}

int main()
{
    Base b;
    Derived d;
    describe(b);
    describe(d);
    return 0;
}