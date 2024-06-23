#include <iostream>
using namespace std;

class Box
{
    int capacity;

public:
    Box() : capacity(0) {}
    Box(double capacity) : capacity(capacity) {}

    bool operator<(const Box &b) const
    {
        return this->capacity < b.capacity;
    }
};

int main()
{
    Box b1(10);
    Box b2 = Box(14);

    if (b1 < b2)
    {
        cout << "B1 is small";
    }
    else
    {
        cout << "B2 is small";
    }
    return 0;
}
