#include <iostream>
using namespace std;

class Base
{
public:
    int x = 1, y = 2;
};

class Derived : public Base
{
public:
    void show()
    {
        cout << x << " " << y << endl;
    }
};

int main(void)
{
    Derived d;
    d.show();
    return 0;
}