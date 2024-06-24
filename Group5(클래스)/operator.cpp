#include <iostream>
using namespace std;

class A
{
    int a;

public:
    A() : a(0) {}
    void show()
    {
        a++;
        cout << "a: " << a << endl;
    }
    // 문법적으로 operator 뒤에 연산자를 지정해야 함
    // 함수 호풀 연산자를 오버로딩하여 객체를 함수처럼 호출
    void operator()() /
    {
        cout << "operator called\n";
    }
};

int main()
{
    A a1, a2;
    a1.show();
    a2.show();

    a1();

    return 0;
}
