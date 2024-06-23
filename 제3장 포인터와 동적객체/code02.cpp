#include <iostream>
using namespace std;

class MyRectangle
{
public:
    MyPoint lu;
    double width, height;
    MyRectangle(double x, double y, double w, double h) : lu(x, y), width(w), height(h) {}

    double area()
    {
        return width * height;
    }
}

MyRectangle r(0.0, 0.0, 2.0, 3.0);

// built-im 타입만이 아니라 클래스 객체에 대한 포인터도 사용가능
MyRectangle *pr = &r;
