#include <iostream>
using namespace std;

// 베이스 클래스 생성자 -> 파생 클래스 생성자 호출
class Base
{
public:
    Base()
    {
        cout << "Base called" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived called" << endl;
    }
};

int main()
{
    Derived d;
    return 0;
}