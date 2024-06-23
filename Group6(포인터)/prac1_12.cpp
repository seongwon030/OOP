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
    Foo *f = new Foo(20);
    cout << f->x << endl; // 객체를 가리키는 포인터변수이므로 화살표연산자사용
    return 0;
}