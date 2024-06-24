#include <iostream>
using namespace std;

class A
{
public:
    static int a;
    void show()
    {
        a++;
        cout << "a: " << a << endl;
    }
};

int A::a = 5;

int main()
{
    A a, b;
    a.show();

    cout << A::a << endl;
    // b 인스턴스로 정적 멤버 변수 a를 10으로
    // 그러나 정적 멤버 변수는 클래스의 모든 인스턴스가 공유하므로
    // 사실상 A::a = 10; 과 같음
    b.a = 10;
    cout << a.a << endl;

    return 0;
}
