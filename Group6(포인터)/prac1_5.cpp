#include <iostream>
using namespace std;

void f(int *p, int *q)
{
    // p 포인터가 q 포인터가 가리키는 주소를 가리킨다
    p = q;
    // p가 가리키는 주소의 값을 2로 설정. q가 가리키는 주소의 값도 2로 설정
    *p = 2;
}

int i = 0, j = 1;
int main()
{
    f(&i, &j);
    // p는 j의 주소를 가리키고 있으므로 j의 값이 2로 변경됨
    cout << i << " " << j << endl;
    return 0;
}
