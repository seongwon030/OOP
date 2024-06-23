#include <iostream>
using namespace std;

int *g()
{
    int *px;
    px = new int;
    *px = 10;
    return px; // 값을 반환
}

int main()
{
    cout << *g();
    return 0;
}
