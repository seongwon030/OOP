#include <iostream>
using namespace std;

class MyPoint
{
public:
    int x;
    int y;
    MyPoint() = default;
    MyPoint(int a, int b) : x(a), y(b) {}
};

void someFunc1(MyPoint s)
{
    MyPoint p(1, 2);
    // s와 p는 동적생성 객체가 아니므로 이 함수가 종료되면 자동 삭제된다. 문제가 없다.
}

MyPoint *someFunc2(MyPoint s)
{
    MyPoint *ptr = new MyPoint(3, 4);
    return ptr;
    // ptr이 가리키는 MyPoint 객체는 동적으로 생성됨.
    // 이 함수 종료되면 포인터 변수 ptr은 자동소멸.
    // 하지만 이 객체 주소를 return하므로 main함수가 이 객체의 주소를 갖는다.
}

void someFunc3()
{
    MyPoint *ptr = new MyPoint(5, 6);
    delete ptr; // ptr이 가리키는 동적생성 객체를 삭제한다.
    // 이 함수가 종료되면 포인터 변수 ptr은 자동소멸.
    // 동적 생성된 객체의 주소를 아무도 기억 못함.
    // delete명령으로 이 객체를 삭제하지 않으면 쓰레기가 된다.
}

int main()
{
    MyPoint a(0, 0);
    someFunc1(a);
    MyPoint *r2 = someFunc2(a);
    someFunc3();
}