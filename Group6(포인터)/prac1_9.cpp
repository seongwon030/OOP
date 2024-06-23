#include <iostream>
using namespace std;

int main()
{
    int arr[10];
    arr[0] = 10;
    int *ptr = &arr[0];
    arr[1] = 20;
    arr[0] = 30;
    cout << *ptr << endl;
    return 0;
}