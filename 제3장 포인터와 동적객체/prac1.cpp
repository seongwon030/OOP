#include <iostream>
using namespace std;

int main()
{
    int c = 12;
    int *p;
    p = &c;

    cout << p << endl;
    cout << *p << endl;

    *p = 20;
    cout << *p << endl;
    return 0;
}