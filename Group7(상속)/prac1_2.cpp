#include <iostream>
using namespace std;

class Base
{
    int arr[10];
};

class Derived : public Base
{
    int d;
};

int main()
{
    // derived는 선언되지 않았음
    // sizeof 는 타입 이름이나 표현식을 필요로 함
    cout << sizeof(Derived);
    return 0;
}

// Base 클래스엔 10개의 정수배열이 있음. 정수가 4byte라면 Base크기는 40
// Derived 클래스에 추가로 정수 d가 있어 4 더해짐