#include <iostream>
using namespace std;

int main()
{
    float arr[5] = {12.5, 10.0, 13.5, 90.5, 0.5};
    float *ptr1 = &arr[0];
    float *ptr2 = ptr1 + 3; // ptr1의 주소에 3을 더함 = 인덱스 3이 더해짐

    cout << *ptr2 << endl;
    cout << ptr2 - ptr1 << endl;

    return 0;
}