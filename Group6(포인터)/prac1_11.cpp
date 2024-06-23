#include <iostream>
using namespace std;

class Foo
{
public:
    int x;
    Foo() = default;
    Foo(int a) : x(a) {}
};

int main()
{
    Foo f(10);
    Foo *ptr = &f;
    // ptr은 Foo 객체를 가리키는 포인터이므로
    // 멤버변수 x에 접근하려면 화살표 연산자를 사용해야 함
    cout << ptr->x << endl;
    return 0;
}