#include <iostream>
using namespace std;

void fun(int *ptr)
{
    // 포인터 변수 ptr이 가리키는 주소의 값을 30으로 변경
    *ptr = 30;
}

int main()
{
    int y = 20;
    // y의 주소를 fun에 전달, y의 값을 30으로 변경
    fun(&y);
    cout << y << endl;
    return 0;
}