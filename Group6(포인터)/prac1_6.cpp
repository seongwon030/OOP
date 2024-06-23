#include <iostream>
using namespace std;

int f(int x, int *py, int **ppz)
{
    int y, z;
    **ppz += 1; // c=4, c->5
    z = **ppz;

    *py += 2; // c=5, c->7
    y = *py;

    x += 3; // c=4, c-> 7
    return x + y + z;
}

int main()
{
    int c, *b, **a;
    c = 4;
    b = &c;
    a = &b;
    cout << f(c, b, a) << endl; // 7+7+5 = 19
    return 0;
}