#include <iostream>
using namespace std;

class A
{
    double d;

public:
    virtual void func()
    {
        // 상속받은 함수에서 이 함수를 재정의 가능
        cout << "In class A\n";
    }
};

class B : public A
{
    int a = 15;

public:
    void func()
    {
        // 부모 클래스의 함수가 가상 함수이기 때문에 이 함수도 가상함수로 작동
        cout << "In class B\n";
    }
};

int main()
{
    B b;
    b.func();
    return 0;
}