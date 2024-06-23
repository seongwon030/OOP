#include <iostream>
using namespace std;

class Base
{
public:
    int x, y;
    Base(int a, int b) : x(a), y(b) {}
};

class Derived : public Base
{
public:
    Derived(int p, int q) : Base(p, q) {}
    void print()
    {
        cout << x << " " << y;
    }
};

int main(void)
{
    Derived q(10, 10);
    q.print();
    return 0;
}