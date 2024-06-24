#include <iostream>
using namespace std;

class complex
{
    int i, j;

public:
    // 기본 생성자 만들어줌
    // operator+ 함수 내부에서 임시 객체 temp 생성 시 기본 생성자 호출
    complex() : i(0), j(0) {}
    complex(int a, int b)
    {
        i = a;
        j = b;
    }

    complex operator+(complex c)
    {
        complex temp;
        temp.i = this->i + c.i;
        temp.j = this->j + c.j;
        return temp;
    }

    void show()
    {
        cout << "Complex Number: " << i << " + i " << j << endl;
    }
};

int main()
{
    complex c1(1, 2);
    complex c2(3, 4);
    complex c3 = c1 + c2;
    c3.show();
    return 0;
}