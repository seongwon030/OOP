#include <iostream>
using namespace std;

class Base
{
    int baseMem;

public:
    Base()
    {
        cout << "Constructing base\n";
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Constructing derived\n";
    }
};

int main()
{
    // 파생클래스의 생성자는 먼저 베이스클래스의 생성자를 호출하여
    // 베이스클래스의 멤버들을 생성하고, 이어서 자신의 추가 멤버들을 생성한다.
    // 소멸자는 그 반대
    Derived d;
    return 0;
}