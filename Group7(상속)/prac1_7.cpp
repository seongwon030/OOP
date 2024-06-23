#include <iostream>
using namespace std;

class Base
{
public:
    void show()
    {
        cout << "In Base";
    }
};

class Derived : public Base
{
public:
    int x;
    void show()
    {
        cout << "In Derived";
    }
    Derived()
    {
        x = 10;
    }
};

int main()
{
    Base *bp, b;
    Derived d;
    bp = &d;
    bp->show();
    // Base 클래스엔 x 멤버 변수 없으므로
    // 기반 클래스 포인터로 파생 클래스의 멤버 변수 x에 접근 못 함
    // cout << bp->x;

    // 올바르게 하려면 파생 클래스 포인터로 캐스팅
    // 멤버 변수 x에 접근 가능
    cout << static_cast<Derived *>(bp)->x;
    return 0;
}