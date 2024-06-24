#include <iostream>
using namespace std;

class myClass
{
    int pra = 5;

public:
    int pub = 10;

    // getter 함수로 private 멤버 변수 pra 값 반환
    int get_pr() const { return pra; }
    void set_pr(int x) { pra = x; }
    void set_pu(int x) { pub = x; }
};

int main()
{
    myClass m;
    int a, b;

    // a = m.pra 에서 변경
    // private 멤버 변수에 접근하는 대신 getter 메서드로 가져옴
    a = m.get_pr();
    b = m.pub;

    m.set_pr(200);
    m.set_pu(200);

    cout << a << endl;
    cout << b << endl;
    cout << m.get_pr() << endl;
    cout << m.pub << endl;
    return 0;
}