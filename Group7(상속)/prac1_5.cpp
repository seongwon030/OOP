#include <iostream>
using namespace std;

class Base
{
    // Base 클래스와 이를 상속받는 클래스에서 접근 가능
protected:
    int x, y;

public:
    Base(int a = 1, int b = 2) : x(a), y(b) {}
};

class Derived : public Base
{
public:
    void show()
    {
        cout << x << " " << y;
    }
};

int main(void)
{
    Derived d;
    d.show();
    return 0;
}