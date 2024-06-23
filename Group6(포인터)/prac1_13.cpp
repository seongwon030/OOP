#include <iostream>
using namespace std;

class Foo
{
public:
    int x;
    Foo() = default;
    Foo(int a) : x(a) {}
};

class Bar
{
public:
    Foo *ptr;
    int z;
    Bar() = default;
    Bar(Foo *p, int a) : ptr(p), z(a) {}
};

int main()
{
    // Foo 객체 동적 생성하여 그 포인터와 정수 20을 이용해 Bar 객체 b를 생성
    // b.ptr은 Foo 객체를 가리키고, b.z는 20으로 초기화됨
    Bar b(new Foo(10), 20);

    // b.ptr이 가리키는 Foo 객체의 x값
    cout << (*b.ptr).x << endl;

    // b.ptr이 가리키는 Foo 객체의 x값
    cout << b.ptr->x << endl;
    return 0;
}