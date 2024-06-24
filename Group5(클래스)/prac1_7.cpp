#include <iostream>
using namespace std;

class Box
{
    int capacity;

public:
    Box() : capacity(0) {}
    Box(double capacity) : capacity(capacity) {}

    // Box 객체끼리의 비교
    // operator 함수 내에서 this 포인터로 객체의 멤버변수를 수정하는 건 capacity 변수를 변경하는 것
    // 그래서 이럴 떈 멤버 함수가 const로 선언되어선 안 됨
    // 따라서 operator 함수를 멤버 변수를 수정하지 않는 const 멤버 함수로 선언하기 위해 두 번째로 붙이는 const가 필요
    // this로 통하는 모든 변수는 해당 함수 내에서 수정될 수 없다 = 이 함수는 멤버 변수의 값을 수정하지 않는다.

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
