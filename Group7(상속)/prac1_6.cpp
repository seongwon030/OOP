#include <iostream>
using namespace std;

class Base
{
};

class Derived : public Base
{
};

int main()
{
    Base *bp = new Derived;
    // 컴파일러는 기반 클래스 객체를 파생 클래스 포인터로 가리키는 것 허용x
    // 파생클래스는 기반 클래스보다 더 많은 멤버를 가질 수 있으므로
    Derived *dp = new Base;
    return 0;
}