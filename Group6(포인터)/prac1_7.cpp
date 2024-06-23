#include <iostream>
using namespace std;

void fun(int *p)
{
    int q = 10;
    p = &q;
}

int main()
{
    int r = 20;
    int *p = &r;
    fun(p);
    cout << *p << endl;
    return 0;
}
// fun에서 p가 q의 주소를 가리키도록 하지만 함수 내에서만 유효하다
// main함수에서 여전히 p는 r의 주소를 가리키므로 20이 출력된다