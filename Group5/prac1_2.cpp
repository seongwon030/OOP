#include <iostream>
using namespace std;

class Box
{
    int capacity;

public:
    Box() {}
    Box(double capacity)
    {
        this->capacity = capacity;
    }

    // private 멤버변수인 capacity에 접근하는 getter함수
    int getCapacity() const
    {
        return capacity;
    }
};

int main()
{
    Box b1(10);
    Box b2 = Box(14);

    cout << b1.getCapacity() << endl; // Output: 10
    cout << b2.getCapacity() << endl; // Output: 14

    return 0;
}
