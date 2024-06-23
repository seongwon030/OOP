#include <iostream>
using namespace std;

class A
{
    int a = 0.;

public:
    A()
    {
        cout << "Object A is created\n";
    }

    void show()
    {
        a++;
        cout << "a: " << a << endl;
    }

    // + 연산자 정의
    A operator+(const A &obj)
    {
        A temp;
        temp.a = this->a + obj.a;
        return temp;
    }
};

int main()
{
    A a1, a2;
    // a1.show();
    // a2.show();
    A a3 = a1 + a2;
    a3.show(); // 더한 값은 2고 show에서 1이 더해진 3이 출력

    return 0;
}
